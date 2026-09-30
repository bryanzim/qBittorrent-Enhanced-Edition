# clang-cl CFG records indirect-call targets but static Qt has no longjmp
# records. Windows then aborts on the first longjmp. Clear only
# IMAGE_GUARD_CF_LONGJUMP_TABLE_PRESENT (0x10000) and leave the CFG
# function table in place.
param(
    [Parameter(Mandatory = $true)]
    [string]$Image
)

$ErrorActionPreference = "Stop"
$LongjmpFlag = [uint32]0x10000

$fs = [System.IO.File]::Open($Image, [System.IO.FileMode]::Open, [System.IO.FileAccess]::ReadWrite)
try {
    $br = New-Object System.IO.BinaryReader $fs
    $bw = New-Object System.IO.BinaryWriter $fs

    function Read-U16([int64]$Position) {
        $fs.Position = $Position
        return $br.ReadUInt16()
    }
    function Read-U32([int64]$Position) {
        $fs.Position = $Position
        return $br.ReadUInt32()
    }

    $pe = Read-U32 0x3C
    $coff = $pe + 4
    $sectionCount = Read-U16 ($coff + 2)
    $optionalSize = Read-U16 ($coff + 16)
    $optional = $coff + 20
    if ((Read-U16 $optional) -ne 0x20B) {
        throw "$Image is not a PE32+ image"
    }

    $loadConfigRva = Read-U32 ($optional + 112 + (10 * 8))
    $loadConfigSize = Read-U32 ($optional + 112 + (10 * 8) + 4)
    if (($loadConfigRva -eq 0) -or ($loadConfigSize -lt 148)) {
        throw "$Image has no CFG load config"
    }

    $section = $optional + $optionalSize
    $loadConfigFile = $null
    for ($i = 0; $i -lt $sectionCount; $i++) {
        $entry = $section + ($i * 40)
        $virtualAddress = Read-U32 ($entry + 12)
        $virtualSize = Read-U32 ($entry + 8)
        $rawSize = Read-U32 ($entry + 16)
        $rawPointer = Read-U32 ($entry + 20)
        $span = [Math]::Max($rawSize, $virtualSize)
        if (($loadConfigRva -ge $virtualAddress) -and ($loadConfigRva -lt ($virtualAddress + $span))) {
            $loadConfigFile = $rawPointer + ($loadConfigRva - $virtualAddress)
            break
        }
    }
    if ($null -eq $loadConfigFile) {
        throw "Could not map the load config of $Image"
    }

    $flagsPosition = $loadConfigFile + 144
    $flags = Read-U32 $flagsPosition
    $updated = $flags -band (-bnot $LongjmpFlag)
    if ($updated -eq $flags) {
        Write-Host "CFG longjmp flag already clear in $Image"
        exit 0
    }

    $fs.Position = $flagsPosition
    $bw.Write([uint32]$updated)
    Write-Host ("Cleared CFG longjmp flag in {0}: 0x{1:X} -> 0x{2:X}" -f $Image, $flags, $updated)
}
finally {
    $fs.Close()
}

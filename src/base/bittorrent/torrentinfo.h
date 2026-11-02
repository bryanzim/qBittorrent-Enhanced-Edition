/*
 * Bittorrent Client using Qt and libtorrent.
 * Copyright (C) 2015-2024  Vladimir Golovnev <glassez@yandex.ru>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * In addition, as a special exception, the copyright holders give permission to
 * link this program with the OpenSSL project's "OpenSSL" library (or with
 * modified versions of it that use the same license as the "OpenSSL" library),
 * and distribute the linked executables. You must obey the GNU General Public
 * License in all respects for all of the code used other than "OpenSSL".  If you
 * modify file(s), you may extend this exception to your version of the file(s),
 * but you are not obligated to do so. If you do not wish to do so, delete this
 * exception statement from your version.
 */

#pragma once

#include "base/indexrange.h"
#include "base/pathfwd.h"

#include <QCoreApplication>
#include <QList>
#include <QtContainerFwd>
#include <libtorrent/torrent_info.hpp>

class QByteArray;
class QDateTime;
class QString;
class QUrl;

namespace BitTorrent
{
    class InfoHash;
    struct TrackerEntry;

    class TorrentInfo
    {
    public:
        TorrentInfo() = default;
        TorrentInfo(const TorrentInfo& other) = default;

        explicit TorrentInfo(const lt::torrent_info& nativeInfo);

        TorrentInfo& operator=(const TorrentInfo& other);

        [[nodiscard]] bool isValid() const;
        [[nodiscard]] InfoHash infoHash() const;
        [[nodiscard]] QString name() const;
        [[nodiscard]] bool isPrivate() const;
        [[nodiscard]] qlonglong totalSize() const;
        [[nodiscard]] int filesCount() const;
        [[nodiscard]] int pieceLength() const;
        [[nodiscard]] int pieceLength(int index) const;
        [[nodiscard]] int piecesCount() const;
        [[nodiscard]] Path filePath(int index) const;
        [[nodiscard]] PathList filePaths() const;
        [[nodiscard]] qlonglong fileSize(int index) const;
        [[nodiscard]] qlonglong fileOffset(int index) const;
        [[nodiscard]] PathList filesForPiece(int pieceIndex) const;
        [[nodiscard]] QList<int> fileIndicesForPiece(int pieceIndex) const;
        [[nodiscard]] QList<QByteArray> pieceHashes() const;

        using PieceRange = IndexRange<int>;
        // returns pair of the first and the last pieces into which
        // the given file extends (maybe partially).
        [[nodiscard]] PieceRange filePieces(const Path& filePath) const;
        [[nodiscard]] PieceRange filePieces(int fileIndex) const;

        [[nodiscard]] QByteArray rawData() const;

        [[nodiscard]] bool matchesInfoHash(const InfoHash& otherInfoHash) const;

        [[nodiscard]] std::shared_ptr<lt::torrent_info> nativeInfo() const;
        [[nodiscard]] QList<lt::file_index_t> nativeIndexes() const;

    private:
        // returns file index or -1 if fileName is not found
        [[nodiscard]] int fileIndex(const Path& filePath) const;

        std::shared_ptr<const lt::torrent_info> m_nativeInfo;

        // internal indexes of files (payload only, excluding any .pad files)
        // by which they are addressed in libtorrent
        QList<lt::file_index_t> m_nativeIndexes;
    };
}

Q_DECLARE_METATYPE(BitTorrent::TorrentInfo)

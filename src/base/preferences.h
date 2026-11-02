/*
 * Bittorrent Client using Qt and libtorrent.
 * Copyright (C) 2014  sledgehammer999 <hammered999@gmail.com>
 * Copyright (C) 2006  Christophe Dumez <chris@qbittorrent.org>
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

#include "base/net/smtpencryptiontype.h"
#include "base/pathfwd.h"
#include "base/utils/net.h"

#include <QObject>
#include <QtContainerFwd>
#include <QtSystemDetection>

class QDateTime;
class QNetworkCookie;
class QTime;

namespace Scheduler
{
    Q_NAMESPACE

    enum class Days : int
    {
        EveryDay = 0,
        Weekday = 1,
        Weekend = 2,
        Monday = 3,
        Tuesday = 4,
        Wednesday = 5,
        Thursday = 6,
        Friday = 7,
        Saturday = 8,
        Sunday = 9
    };
    Q_ENUM_NS(Days)
}

namespace DNS
{
    Q_NAMESPACE

    enum class Service : int
    {
        DynDNS = 0,
        NoIP = 1,
        None = -1
    };
    Q_ENUM_NS(Service)
}

class Preferences final : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(Preferences)

    Preferences();

public:
    static void initInstance();
    static void freeInstance();
    static Preferences* instance();

    // General options
    [[nodiscard]] QString getLocale() const;
    void setLocale(const QString& locale);
    [[nodiscard]] bool useCustomUITheme() const;
    void setUseCustomUITheme(bool use);
    [[nodiscard]] Path customUIThemePath() const;
    void setCustomUIThemePath(const Path& path);
    [[nodiscard]] bool removeTorrentContent() const;
    void setRemoveTorrentContent(bool remove);
    [[nodiscard]] bool confirmOnExit() const;
    void setConfirmOnExit(bool confirm);
    [[nodiscard]] bool speedInTitleBar() const;
    void showSpeedInTitleBar(bool show);
    [[nodiscard]] bool useAlternatingRowColors() const;
    void setAlternatingRowColors(bool b);
    [[nodiscard]] bool useTorrentStatesColors() const;
    void setUseTorrentStatesColors(bool value);
    [[nodiscard]] bool getProgressBarFollowsTextColor() const;
    void setProgressBarFollowsTextColor(bool value);
    [[nodiscard]] bool getHideZeroValues() const;
    void setHideZeroValues(bool b);
    [[nodiscard]] int getHideZeroComboValues() const;
    void setHideZeroComboValues(int n);
    [[nodiscard]] bool isStatusbarDisplayed() const;
    void setStatusbarDisplayed(bool displayed);
    [[nodiscard]] bool isStatusbarFreeDiskSpaceDisplayed() const;
    void setStatusbarFreeDiskSpaceDisplayed(bool displayed);
    [[nodiscard]] bool isStatusbarExternalIPDisplayed() const;
    void setStatusbarExternalIPDisplayed(bool displayed);
    [[nodiscard]] bool isToolbarDisplayed() const;
    void setToolbarDisplayed(bool displayed);
    [[nodiscard]] bool isTorrentContentDragEnabled() const;
    void setTorrentContentDragEnabled(bool enabled);
    [[nodiscard]] bool isSplashScreenDisabled() const;
    void setSplashScreenDisabled(bool b);
    [[nodiscard]] bool preventFromSuspendWhenDownloading() const;
    void setPreventFromSuspendWhenDownloading(bool b);
    [[nodiscard]] bool preventFromSuspendWhenSeeding() const;
    void setPreventFromSuspendWhenSeeding(bool b);
    [[nodiscard]] QString getStyle() const;
    void setStyle(const QString& styleName);
#ifdef Q_OS_WIN
    [[nodiscard]] bool WinStartup() const;
    void setWinStartup(bool b);
#endif

    // Downloads
    [[nodiscard]] Path getScanDirsLastPath() const;
    void setScanDirsLastPath(const Path& path);
    [[nodiscard]] bool isMailNotificationEnabled() const;
    void setMailNotificationEnabled(bool enabled);
    [[nodiscard]] QString getMailNotificationSender() const;
    void setMailNotificationSender(const QString& mail);
    [[nodiscard]] QString getMailNotificationEmail() const;
    void setMailNotificationEmail(const QString& mail);
    [[nodiscard]] QString getMailNotificationSMTP() const;
    void setMailNotificationSMTP(const QString& smtpServer);
    [[nodiscard]] Net::SMTPEncryptionType getMailNotificationSMTPEncryptionType() const;
    void setMailNotificationSMTPEncryptionType(Net::SMTPEncryptionType mailEncryptionType);
    [[nodiscard]] bool getMailNotificationSMTPAuth() const;
    void setMailNotificationSMTPAuth(bool use);
    [[nodiscard]] QString getMailNotificationSMTPUsername() const;
    void setMailNotificationSMTPUsername(const QString& username);
    [[nodiscard]] QString getMailNotificationSMTPPassword() const;
    void setMailNotificationSMTPPassword(const QString& password);
    [[nodiscard]] int getActionOnDblClOnTorrentDl() const;
    void setActionOnDblClOnTorrentDl(int act);
    [[nodiscard]] int getActionOnDblClOnTorrentFn() const;
    void setActionOnDblClOnTorrentFn(int act);

    // Connection options
    [[nodiscard]] QTime getSchedulerStartTime() const;
    void setSchedulerStartTime(const QTime& time);
    [[nodiscard]] QTime getSchedulerEndTime() const;
    void setSchedulerEndTime(const QTime& time);
    [[nodiscard]] Scheduler::Days getSchedulerDays() const;
    void setSchedulerDays(Scheduler::Days days);

    // Search
    [[nodiscard]] bool isSearchEnabled() const;
    void setSearchEnabled(bool enabled);

    // Search UI
    [[nodiscard]] int searchHistoryLength() const;
    void setSearchHistoryLength(int length);
    [[nodiscard]] bool storeSearchJobs() const;
    void setStoreSearchJobs(bool enabled);
    [[nodiscard]] bool storeSearchJobResults() const;
    void setStoreSearchJobResults(bool enabled);
    [[nodiscard]] bool closeSearchTabWithMiddleClick() const;
    void setCloseSearchTabWithMiddleClick(bool enabled);

    // HTTP Server
    [[nodiscard]] bool isWebUIEnabled() const;
    void setWebUIEnabled(bool enabled);
    [[nodiscard]] QString getServerDomains() const;
    void setServerDomains(const QString& str);
    [[nodiscard]] QString getWebUIAddress() const;
    void setWebUIAddress(const QString& addr);
    [[nodiscard]] quint16 getWebUIPort() const;
    void setWebUIPort(quint16 port);
    [[nodiscard]] bool useUPnPForWebUIPort() const;
    void setUPnPForWebUIPort(bool enabled);

    // Authentication
    [[nodiscard]] bool isWebUILocalAuthEnabled() const;
    void setWebUILocalAuthEnabled(bool enabled);
    [[nodiscard]] bool isWebUIAuthSubnetWhitelistEnabled() const;
    void setWebUIAuthSubnetWhitelistEnabled(bool enabled);
    [[nodiscard]] QList<Utils::Net::Subnet> getWebUIAuthSubnetWhitelist() const;
    void setWebUIAuthSubnetWhitelist(QStringList subnets);
    [[nodiscard]] QString getWebUIUsername() const;
    void setWebUIUsername(const QString& username);
    [[nodiscard]] QByteArray getWebUIPassword() const;
    void setWebUIPassword(const QByteArray& password);
    [[nodiscard]] QString getWebUIApiKey() const;
    void setWebUIApiKey(const QString& apiKey);
    [[nodiscard]] int getWebUIMaxAuthFailCount() const;
    void setWebUIMaxAuthFailCount(int count);
    [[nodiscard]] std::chrono::seconds getWebUIBanDuration() const;
    void setWebUIBanDuration(std::chrono::seconds duration);
    [[nodiscard]] int getWebUISessionTimeout() const;
    void setWebUISessionTimeout(int timeout);
    [[nodiscard]] int getWebUISessionsCountLimit() const;
    void setWebUISessionsCountLimit(int limit);

    // WebUI security
    [[nodiscard]] bool isWebUIClickjackingProtectionEnabled() const;
    void setWebUIClickjackingProtectionEnabled(bool enabled);
    [[nodiscard]] bool isWebUICSRFProtectionEnabled() const;
    void setWebUICSRFProtectionEnabled(bool enabled);
    [[nodiscard]] bool isWebUISecureCookieEnabled() const;
    void setWebUISecureCookieEnabled(bool enabled);
    [[nodiscard]] bool isWebUIHostHeaderValidationEnabled() const;
    void setWebUIHostHeaderValidationEnabled(bool enabled);

    // HTTPS
    [[nodiscard]] bool isWebUIHttpsEnabled() const;
    void setWebUIHttpsEnabled(bool enabled);
    [[nodiscard]] Path getWebUIHttpsCertificatePath() const;
    void setWebUIHttpsCertificatePath(const Path& path);
    [[nodiscard]] Path getWebUIHttpsKeyPath() const;
    void setWebUIHttpsKeyPath(const Path& path);
    [[nodiscard]] bool isAltWebUIEnabled() const;
    void setAltWebUIEnabled(bool enabled);
    [[nodiscard]] Path getWebUIRootFolder() const;
    void setWebUIRootFolder(const Path& path);

    // WebUI custom HTTP headers
    [[nodiscard]] bool isWebUICustomHTTPHeadersEnabled() const;
    void setWebUICustomHTTPHeadersEnabled(bool enabled);
    [[nodiscard]] QString getWebUICustomHTTPHeaders() const;
    void setWebUICustomHTTPHeaders(const QString& headers);

    // Reverse proxy
    [[nodiscard]] bool isWebUIReverseProxySupportEnabled() const;
    void setWebUIReverseProxySupportEnabled(bool enabled);
    [[nodiscard]] QString getWebUITrustedReverseProxiesList() const;
    void setWebUITrustedReverseProxiesList(const QString& addr);

    // Dynamic DNS
    [[nodiscard]] bool isDynDNSEnabled() const;
    void setDynDNSEnabled(bool enabled);
    [[nodiscard]] DNS::Service getDynDNSService() const;
    void setDynDNSService(DNS::Service service);
    [[nodiscard]] QString getDynDomainName() const;
    void setDynDomainName(const QString& name);
    [[nodiscard]] QString getDynDNSUsername() const;
    void setDynDNSUsername(const QString& username);
    [[nodiscard]] QString getDynDNSPassword() const;
    void setDynDNSPassword(const QString& password);

    // Advanced settings
    [[nodiscard]] QByteArray getUILockPassword() const;
    void setUILockPassword(const QByteArray& password);
    [[nodiscard]] bool isUILocked() const;
    void setUILocked(bool locked);

    [[nodiscard]] bool isAutoRunOnTorrentAddedEnabled() const;
    void setAutoRunOnTorrentAddedEnabled(bool enabled);
    [[nodiscard]] QString getAutoRunOnTorrentAddedProgram() const;
    void setAutoRunOnTorrentAddedProgram(const QString& program);
    [[nodiscard]] bool isAutoRunOnTorrentFinishedEnabled() const;
    void setAutoRunOnTorrentFinishedEnabled(bool enabled);
    [[nodiscard]] QString getAutoRunOnTorrentFinishedProgram() const;
    void setAutoRunOnTorrentFinishedProgram(const QString& program);
#if defined(Q_OS_WIN)
    [[nodiscard]] bool isAutoRunConsoleEnabled() const;
    void setAutoRunConsoleEnabled(bool enabled);
#endif

    [[nodiscard]] bool shutdownWhenDownloadsComplete() const;
    void setShutdownWhenDownloadsComplete(bool shutdown);
    [[nodiscard]] bool rebootWhenDownloadsComplete() const;
    void setRebootWhenDownloadsComplete(bool reboot);
    [[nodiscard]] bool suspendWhenDownloadsComplete() const;
    void setSuspendWhenDownloadsComplete(bool suspend);
    [[nodiscard]] bool hibernateWhenDownloadsComplete() const;
    void setHibernateWhenDownloadsComplete(bool hibernate);
    [[nodiscard]] bool shutdownqBTWhenDownloadsComplete() const;
    void setShutdownqBTWhenDownloadsComplete(bool shutdown);
    [[nodiscard]] bool dontConfirmAutoExit() const;
    void setDontConfirmAutoExit(bool dontConfirmAutoExit);
    [[nodiscard]] bool recheckTorrentsOnCompletion() const;
    void recheckTorrentsOnCompletion(bool recheck);
    [[nodiscard]] bool resolvePeerCountries() const;
    void resolvePeerCountries(bool resolve);
    [[nodiscard]] bool resolvePeerHostNames() const;
    void resolvePeerHostNames(bool resolve);
#if (defined(Q_OS_UNIX) && !defined(Q_OS_MACOS))
    bool useSystemIcons() const;
    void useSystemIcons(bool enabled);
#endif
    [[nodiscard]] bool isRecursiveDownloadEnabled() const;
    void setRecursiveDownloadEnabled(bool enable);
    [[nodiscard]] int getTrackerPort() const;
    void setTrackerPort(int port);
    [[nodiscard]] bool isTrackerPortForwardingEnabled() const;
    void setTrackerPortForwardingEnabled(bool enabled);
    [[nodiscard]] bool isMarkOfTheWebEnabled() const;
    void setMarkOfTheWebEnabled(bool enabled);
    [[nodiscard]] bool isIgnoreSSLErrors() const;
    void setIgnoreSSLErrors(bool enabled);
    [[nodiscard]] Path getPythonExecutablePath() const;
    void setPythonExecutablePath(const Path& path);
#if defined(Q_OS_WIN) || defined(Q_OS_MACOS)
    [[nodiscard]] bool isUpdateCheckEnabled() const;
    void setUpdateCheckEnabled(bool enabled);
#endif
#ifdef Q_OS_MACOS
    bool isSpeedInDockEnabled() const;
    void setSpeedInDockEnabled(bool enabled);
    bool isMacOSMenuBarIconEnabled() const;
    void setMacOSMenuBarIconEnabled(bool enabled);
#endif
    [[nodiscard]] bool confirmTorrentDeletion() const;
    void setConfirmTorrentDeletion(bool enabled);
    [[nodiscard]] bool confirmTorrentRecheck() const;
    void setConfirmTorrentRecheck(bool enabled);
    [[nodiscard]] bool confirmRemoveAllTags() const;
    void setConfirmRemoveAllTags(bool enabled);
    [[nodiscard]] bool confirmMergeTrackers() const;
    void setConfirmMergeTrackers(bool enabled);
    [[nodiscard]] bool confirmRemoveTrackerFromAllTorrents() const;
    void setConfirmRemoveTrackerFromAllTorrents(bool enabled);
#ifndef Q_OS_MACOS
    [[nodiscard]] bool systemTrayEnabled() const;
    void setSystemTrayEnabled(bool enabled);
    [[nodiscard]] bool minimizeToTrayNotified() const;
    void setMinimizeToTrayNotified(bool b);
    [[nodiscard]] bool minimizeToTray() const;
    void setMinimizeToTray(bool b);
    [[nodiscard]] bool closeToTray() const;
    void setCloseToTray(bool b);
    [[nodiscard]] bool closeToTrayNotified() const;
    void setCloseToTrayNotified(bool b);
    [[nodiscard]] bool iconsInMenusEnabled() const;
    void setIconsInMenusEnabled(bool enable);
#endif // Q_OS_MACOS
    [[nodiscard]] qint64 getTorrentFileSizeLimit() const;
    void setTorrentFileSizeLimit(qint64 value);
    [[nodiscard]] int getBdecodeDepthLimit() const;
    void setBdecodeDepthLimit(int value);
    [[nodiscard]] int getBdecodeTokenLimit() const;
    void setBdecodeTokenLimit(int value);

    // Stuff that don't appear in the Options GUI but are saved
    // in the same file.
    [[nodiscard]] QDateTime getDNSLastUpd() const;
    void setDNSLastUpd(const QDateTime& date);
    [[nodiscard]] QString getDNSLastIP() const;
    void setDNSLastIP(const QString& ip);
    [[nodiscard]] QByteArray getMainGeometry() const;
    void setMainGeometry(const QByteArray& geometry);
    [[nodiscard]] bool isFiltersSidebarVisible() const;
    void setFiltersSidebarVisible(bool value);
    [[nodiscard]] int getFiltersSidebarWidth() const;
    void setFiltersSidebarWidth(int value);
    [[nodiscard]] Path getMainLastDir() const;
    void setMainLastDir(const Path& path);
    [[nodiscard]] QByteArray getPeerListState() const;
    void setPeerListState(const QByteArray& state);
    [[nodiscard]] QString getPropSplitterSizes() const;
    void setPropSplitterSizes(const QString& sizes);
    [[nodiscard]] QByteArray getPropFileListState() const;
    void setPropFileListState(const QByteArray& state);
    [[nodiscard]] int getPropCurTab() const;
    void setPropCurTab(int tab);
    [[nodiscard]] bool getPropVisible() const;
    void setPropVisible(bool visible);
    [[nodiscard]] QByteArray getTrackerListState() const;
    void setTrackerListState(const QByteArray& state);
    [[nodiscard]] QStringList getRssOpenFolders() const;
    void setRssOpenFolders(const QStringList& folders);
    [[nodiscard]] QByteArray getRssFeedListState() const;
    void setRssFeedListState(const QByteArray& state);
    [[nodiscard]] QByteArray getRssSideSplitterState() const;
    void setRssSideSplitterState(const QByteArray& state);
    [[nodiscard]] QByteArray getRssMainSplitterState() const;
    void setRssMainSplitterState(const QByteArray& state);
    [[nodiscard]] QByteArray getSearchTabHeaderState() const;
    void setSearchTabHeaderState(const QByteArray& state);
    [[nodiscard]] bool getRegexAsFilteringPatternForSearchJob() const;
    void setRegexAsFilteringPatternForSearchJob(bool checked);
    [[nodiscard]] QStringList getSearchEngDisabled() const;
    void setSearchEngDisabled(const QStringList& engines);
    [[nodiscard]] QString getTorImportLastContentDir() const;
    void setTorImportLastContentDir(const QString& path);
    [[nodiscard]] QByteArray getTorImportGeometry() const;
    void setTorImportGeometry(const QByteArray& geometry);
    [[nodiscard]] bool getStatusFilterState() const;
    [[nodiscard]] bool getCategoryFilterState() const;
    [[nodiscard]] bool getTagFilterState() const;
    [[nodiscard]] bool getTrackerFilterState() const;
    [[nodiscard]] bool getTrackerStatusFilterState() const;
    [[nodiscard]] bool useSeparateTrackerStatusFilter() const;
    void setUseSeparateTrackerStatusFilter(bool value);
    [[nodiscard]] int getTransSelFilter() const;
    void setTransSelFilter(int index);
    [[nodiscard]] bool getHideZeroStatusFilters() const;
    void setHideZeroStatusFilters(bool hide);
    [[nodiscard]] QByteArray getTransHeaderState() const;
    void setTransHeaderState(const QByteArray& state);
    [[nodiscard]] bool getRegexAsFilteringPatternForTransferList() const;
    void setRegexAsFilteringPatternForTransferList(bool checked);
    [[nodiscard]] int getToolbarTextPosition() const;
    void setToolbarTextPosition(int position);

    // From old RssSettings class
    [[nodiscard]] bool isRSSWidgetEnabled() const;
    void setRSSWidgetVisible(bool enabled);

    // Network
    [[nodiscard]] QList<QNetworkCookie> getNetworkCookies() const;
    void setNetworkCookies(const QList<QNetworkCookie>& cookies);

    [[nodiscard]] bool useProxyForBT() const;
    void setUseProxyForBT(bool value);
    [[nodiscard]] bool useProxyForRSS() const;
    void setUseProxyForRSS(bool value);
    [[nodiscard]] bool useProxyForGeneralPurposes() const;
    void setUseProxyForGeneralPurposes(bool value);

    // SpeedWidget
    [[nodiscard]] bool isSpeedWidgetEnabled() const;
    void setSpeedWidgetEnabled(bool enabled);
    [[nodiscard]] int getSpeedWidgetPeriod() const;
    void setSpeedWidgetPeriod(int period);
    [[nodiscard]] bool getSpeedWidgetGraphEnable(int id) const;
    void setSpeedWidgetGraphEnable(int id, bool enable);

    // AddNewTorrentDialog
    [[nodiscard]] bool isAddNewTorrentDialogEnabled() const;
    void setAddNewTorrentDialogEnabled(bool value);
    [[nodiscard]] bool isAddNewTorrentDialogTopLevel() const;
    void setAddNewTorrentDialogTopLevel(bool value);
    [[nodiscard]] int addNewTorrentDialogSavePathHistoryLength() const;
    void setAddNewTorrentDialogSavePathHistoryLength(int value);
    [[nodiscard]] bool isAddNewTorrentDialogAttached() const;
    void setAddNewTorrentDialogAttached(bool attached);

    // Enhanced option
    [[nodiscard]] bool getAutoBanUnknownPeer() const;
    void setAutoBanUnknownPeer(bool checked);
    [[nodiscard]] bool getAutoBanBTPlayerPeer() const;
    void setAutoBanBTPlayerPeer(bool checked);
    [[nodiscard]] bool getShadowBan() const;
    void setShadowBan(bool checked);
    [[nodiscard]] bool isCookieExpirationEnabled() const;
    void setCookieExpirationEnabled(bool enabled);
    [[nodiscard]] QString getTrackersListUrl() const;
    [[nodiscard]] bool isAutoUpdateTrackersEnabled() const;

    void setMigrateStatus(bool enabled);
    [[nodiscard]] bool getMigrateStatus() const;

public slots:
    void setStatusFilterState(bool checked);
    void setCategoryFilterState(bool checked);
    void setTagFilterState(bool checked);
    void setTrackerFilterState(bool checked);
    void setTrackerStatusFilterState(bool checked);

    void apply();

signals:
    void changed();

private:
    static Preferences* m_instance;
};

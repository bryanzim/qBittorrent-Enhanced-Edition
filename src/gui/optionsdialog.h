/*
 * Bittorrent Client using Qt and libtorrent.
 * Copyright (C) 2023-2024  Vladimir Golovnev <glassez@yandex.ru>
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

#include "base/net/downloadmanager.h"
#include "base/net/proxytype.h"
#include "base/pathfwd.h"
#include "base/settingvalue.h"
#include "guiapplicationcomponent.h"

#include <QDialog>

class QListWidgetItem;

class AdvancedSettings;

// actions on double-click on torrents
enum DoubleClickAction
{
    TOGGLE_STOP = 0,
    OPEN_DEST = 1,
    PREVIEW_FILE = 2,
    NO_ACTION = 3,
    SHOW_OPTIONS = 4
};

namespace Ui
{
    class OptionsDialog;
}

class OptionsDialog final : public GUIApplicationComponent<QDialog>
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(OptionsDialog)

    using ThisType = OptionsDialog;

    enum Tabs
    {
        TAB_UI,
        TAB_DOWNLOADS,
        TAB_CONNECTION,
        TAB_SPEED,
        TAB_BITTORRENT,
        TAB_SEARCH,
        TAB_RSS,
        TAB_WEBUI,
        TAB_ADVANCED
    };

public:
    explicit OptionsDialog(IGUIApplication* app, QWidget* parent = nullptr);
    ~OptionsDialog() override;

public slots:
    void showConnectionTab();
    void showSpeedWidgetSetting();
    void showRSSTab();

private slots:
    void adjustProxyOptions();
    void changeSMTPEncryptionPortInfoLabel();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void enableApplyButton();
    void toggleComboRatioLimitAct();
    void changePage(QListWidgetItem*, QListWidgetItem*);
    void loadSplitterState();
    void handleWatchedFolderViewSelectionChanged();
    void editWatchedFolderOptions(const QModelIndex& index);
    void on_IpFilterRefreshBtn_clicked();
    void handleIPFilterParsed(bool error, int ruleCount);
    void on_banListButton_clicked();
    void on_shadowBanListButton_clicked();
    void on_IPSubnetWhitelistButton_clicked();
    void on_randomButton_clicked();
    void on_addWatchedFolderButton_clicked();
    void on_editWatchedFolderButton_clicked();
    void on_removeWatchedFolderButton_clicked();
    void setLocale(const QString& localeStr);

#ifndef DISABLE_WEBUI
    void webUIHttpsCertChanged(const Path& path);
    void webUIHttpsKeyChanged(const Path& path);
    void on_registerDNSBtn_clicked();
    void onBtnWebUIAPIKeyCopyClicked();
    void onBtnWebUIAPIKeyRotateClicked();
    void onBtnWebUIAPIKeyDeleteClicked();
    void setupWebUIAPIKey();
#endif

private:
    void showEvent(QShowEvent* e) override;

    // Methods
    bool applySettings();
    void saveOptions() const;

    void loadBehaviorTabOptions();
    void saveBehaviorTabOptions() const;

    void loadDownloadsTabOptions();
    void saveDownloadsTabOptions() const;

    void loadConnectionTabOptions();
    void saveConnectionTabOptions() const;

    void loadSpeedTabOptions();
    void saveSpeedTabOptions() const;

    void loadBittorrentTabOptions();
    void saveBittorrentTabOptions() const;

    void loadRSSTabOptions();
    void saveRSSTabOptions() const;

    void loadSearchTabOptions();
    void saveSearchTabOptions() const;

#ifndef DISABLE_WEBUI
    void loadWebUITabOptions();
    void saveWebUITabOptions() const;
#endif // DISABLE_WEBUI

    // General options
    void initializeLanguageCombo();
    void initializeStyleCombo();
    void initializeColorSchemeOptions();
    [[nodiscard]] QString getLocale() const;
    [[nodiscard]] bool isSplashScreenDisabled() const;
#ifdef Q_OS_WIN
    [[nodiscard]] bool WinStartup() const;
#endif
    // Downloads
    [[nodiscard]] bool preAllocateAllFiles() const;
    [[nodiscard]] bool useAdditionDialog() const;
    [[nodiscard]] bool addTorrentsStopped() const;
    // Connection options
    [[nodiscard]] int getPort() const;
    [[nodiscard]] bool isUPnPEnabled() const;
    // Bittorrent options
    [[nodiscard]] int getMaxConnections() const;
    [[nodiscard]] int getMaxConnectionsPerTorrent() const;
    [[nodiscard]] int getMaxUploads() const;
    [[nodiscard]] int getMaxUploadsPerTorrent() const;
    [[nodiscard]] bool isDHTEnabled() const;
    [[nodiscard]] bool isLSDEnabled() const;
    [[nodiscard]] int getEncryptionSetting() const;
    [[nodiscard]] qreal getMaxRatio() const;
    [[nodiscard]] int getMaxSeedingMinutes() const;
    [[nodiscard]] int getMaxInactiveSeedingMinutes() const;
    // Proxy options
    [[nodiscard]] bool isProxyEnabled() const;
    [[nodiscard]] QString getProxyIp() const;
    [[nodiscard]] unsigned short getProxyPort() const;
    [[nodiscard]] QString getProxyUsername() const;
    [[nodiscard]] QString getProxyPassword() const;
    [[nodiscard]] Net::ProxyType getProxyType() const;
    // IP Filter
    [[nodiscard]] bool isIPFilteringEnabled() const;
    [[nodiscard]] Path getFilter() const;
    [[nodiscard]] bool isShadowBanEnabled() const;
    // Queueing system
    [[nodiscard]] bool isQueueingSystemEnabled() const;
    [[nodiscard]] int getMaxActiveDownloads() const;
    [[nodiscard]] int getMaxActiveUploads() const;
    [[nodiscard]] int getMaxActiveTorrents() const;
    // WebUI
#ifndef DISABLE_WEBUI
    [[nodiscard]] bool isWebUIEnabled() const;
    [[nodiscard]] QString webUIUsername() const;
    [[nodiscard]] QString webUIPassword() const;
    bool webUIAuthenticationOk();
    bool isAlternativeWebUIPathValid();
#endif

    bool schedTimesOk();

    Ui::OptionsDialog* m_ui = nullptr;
    SettingValue<QSize> m_storeDialogSize;
    SettingValue<QStringList> m_storeHSplitterSize;
    SettingValue<int> m_storeLastViewedPage;

    QPushButton* m_applyButton = nullptr;

    AdvancedSettings* m_advancedSettings = nullptr;

    bool m_refreshingIpFilter = false;

#ifndef DISABLE_WEBUI
    QString m_currentAPIKey;
#endif
};

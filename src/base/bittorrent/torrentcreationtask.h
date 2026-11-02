/*
 * Bittorrent Client using Qt and libtorrent.
 * Copyright (C) 2024  Vladimir Golovnev <glassez@yandex.ru>
 * Copyright (C) 2024  Radu Carpa <radu.carpa@cern.ch>
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

#include "base/applicationcomponent.h"
#include "torrentcreator.h"

#include <QDateTime>
#include <QObject>
#include <QString>

namespace BitTorrent
{
    class TorrentCreationTask final : public ApplicationComponent<QObject>
    {
        Q_OBJECT
        Q_DISABLE_COPY_MOVE(TorrentCreationTask)

    public:
        enum State
        {
            Queued,
            Running,
            Finished
        };

        TorrentCreationTask(IApplication* app, const QString& id, TorrentCreator* torrentCreator, bool startSeeding, QObject* parent = nullptr);

        [[nodiscard]] QString id() const;
        [[nodiscard]] const TorrentCreatorParams& params() const;
        [[nodiscard]] State state() const;
        [[nodiscard]] bool isQueued() const;
        [[nodiscard]] bool isRunning() const;
        [[nodiscard]] bool isFinished() const;
        [[nodiscard]] bool isFailed() const;
        [[nodiscard]] QDateTime timeAdded() const;
        [[nodiscard]] QDateTime timeStarted() const;
        [[nodiscard]] QDateTime timeFinished() const;
        [[nodiscard]] int progress() const;
        [[nodiscard]] const TorrentCreatorResult& result() const;
        [[nodiscard]] QString errorMsg() const;

    private:
        QString m_id;
        TorrentCreatorParams m_params;
        QDateTime m_timeAdded;
        QDateTime m_timeStarted;
        QDateTime m_timeFinished;
        int m_progress = 0;
        TorrentCreatorResult m_result;
        QString m_errorMsg;
    };
}

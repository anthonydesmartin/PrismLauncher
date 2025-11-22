// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Prism Launcher - Minecraft Launcher
 *  Copyright (C) 2022 Sefa Eyeoglu <contact@scrumplex.net>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 3.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *
 *      Copyright 2013-2021 MultiMC Contributors
 *
 *      Licensed under the Apache License, Version 2.0 (the "License");
 *      you may not use this file except in compliance with the License.
 *      You may obtain a copy of the License at
 *
 *          http://www.apache.org/licenses/LICENSE-2.0
 *
 *      Unless required by applicable law or agreed to in writing, software
 *      distributed under the License is distributed on an "AS IS" BASIS,
 *      WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *      See the License for the specific language governing permissions and
 *      limitations under the License.
 */

#pragma once

#include "BaseInstance.h"
#include "InstanceCreationTask.h"

#include <optional>

#include "minecraft/MinecraftInstance.h"

#include "modplatform/flame/FileResolvingTask.h"

#include "net/NetJob.h"

#include "ui/dialogs/BlockedModsDialog.h"

class FlameCreationTask final : public InstanceCreationTask {
    Q_OBJECT

   public:
    FlameCreationTask(const QString& stagingPath,
                      SettingsObjectPtr globalSettings,
                      QWidget* parent,
                      QString id,
                      QString versionId,
                      QString originalInstanceId = {})
        : InstanceCreationTask(), m_parent(parent), m_managedId(std::move(id)), m_managedVersionId(std::move(versionId))
    {
        setStagingPath(stagingPath);
        setParentSettings(globalSettings);

        m_originalInstanceId = std::move(originalInstanceId);
    }

    bool abort() override;

    void createInstance();
    void executeTask() override;

   private slots:
    void idResolverSucceeded();
    void setupDownloadJob();
    void copyBlockedMods(QList<BlockedMod> const& blockedMods);
    void validateOtherResources();
    QString getVersionForLoader(QString uid, QString loaderType, QString version, QString mcVersion);
    void finishInstall();

   private:
    void setManagedPack(BaseInstance* instance);

   private:
    QWidget* m_parent = nullptr;

    shared_qobject_ptr<Flame::FileResolvingTask> m_modIdResolver;
    Flame::Manifest m_pack;

    // Handle to allow aborting
    Task::Ptr m_processUpdateFileInfoJob = nullptr;
    NetJob::Ptr m_filesJob = nullptr;

    QString m_managedId, m_managedVersionId;

    QList<std::pair<QString, QString>> m_otherResources;

    std::optional<InstancePtr> m_instance;

    QStringList m_selectedOptionalMods;

    QStringList m_filesToRemove;
};

#pragma once

#include "settings/SettingsObject.h"
#include "tasks/Task.h"

/* Helpers */
enum class InstanceNameChange { ShouldChange, ShouldKeep };
[[nodiscard]] InstanceNameChange askForChangingInstanceName(QWidget* parent, const QString& oldName, const QString& newName);
enum class ShouldUpdate { Update, SkipUpdating, Cancel };
[[nodiscard]] ShouldUpdate askIfShouldUpdate(QWidget* parent, QString originalVersionName);

class InstanceCreationTask : public Task {
   public:
    InstanceCreationTask() {}
    virtual ~InstanceCreationTask() = default;

    void setParentSettings(SettingsObjectPtr settings) { m_globalSettings = settings; }

    void setStagingPath(const QString& stagingPath) { m_stagingPath = stagingPath; }

    void setIcon(const QString& icon) { m_instIcon = icon; }

    void setGroup(const QString& group) { m_instGroup = group; }
    QString group() const { return m_instGroup; }

    bool shouldConfirmUpdate() const { return m_confirmUpdate; }
    void setConfirmUpdate(bool confirm) { m_confirmUpdate = confirm; }

    bool shouldOverride() const { return m_overrideExisting; }

    QString originalInstanceID() const { return m_originalInstanceId; };

    QString modifiedName() const;
    QString originalName() const;
    QString name() const;
    QString version() const;

    void setName(QString name) { m_modifiedName = name; }
    void setOriginalName(QString name, QString version);

   protected:
    void setOverride(bool override, QString instanceIdToOverride = {})
    {
        m_overrideExisting = override;
        if (!instanceIdToOverride.isEmpty())
            m_originalInstanceId = instanceIdToOverride;
    }

   protected: /* data */
    QString m_originalName;
    QString m_originalVersion;

    QString m_modifiedName;

    SettingsObjectPtr m_globalSettings;
    QString m_instIcon;
    QString m_instGroup;
    QString m_stagingPath;

    bool m_overrideExisting = false;
    bool m_confirmUpdate = true;

    QString m_originalInstanceId;
};

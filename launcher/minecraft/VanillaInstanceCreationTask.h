#pragma once

#include "BaseVersion.h"
#include "InstanceCreationTask.h"

class VanillaCreationTask final : public InstanceCreationTask {
    Q_OBJECT
   public:
    VanillaCreationTask(BaseVersion::Ptr version) : InstanceCreationTask(), m_version(std::move(version)) {}
    VanillaCreationTask(BaseVersion::Ptr version, QString loader, BaseVersion::Ptr loader_version);

    void executeTask() override;

   private:
    // Version to update to / create of the instance.
    BaseVersion::Ptr m_version;

    bool m_usingLoader = false;
    QString m_loader;
    BaseVersion::Ptr m_loaderVersion;
};

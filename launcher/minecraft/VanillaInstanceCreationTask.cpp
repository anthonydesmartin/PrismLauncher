#include "VanillaInstanceCreationTask.h"

#include <utility>

#include "FileSystem.h"
#include "minecraft/MinecraftInstance.h"
#include "minecraft/PackProfile.h"
#include "settings/INISettingsObject.h"

VanillaCreationTask::VanillaCreationTask(BaseVersion::Ptr version, QString loader, BaseVersion::Ptr loaderVersion)
    : InstanceCreationTask()
    , m_version(std::move(version))
    , m_usingLoader(true)
    , m_loader(std::move(loader))
    , m_loaderVersion(std::move(loaderVersion))
{}

void VanillaCreationTask::executeTask()
{
    setStatus(tr("Creating instance from version %1").arg(m_version->name()));

    auto instanceSettings = std::make_shared<INISettingsObject>(FS::PathCombine(m_stagingPath, "instance.cfg"));
    instanceSettings->suspendSave();
    {
        MinecraftInstance inst(m_globalSettings, instanceSettings, m_stagingPath);
        auto components = inst.getPackProfile();
        components->buildingFromScratch();
        components->setComponentVersion("net.minecraft", m_version->descriptor(), true);
        if (m_usingLoader)
            components->setComponentVersion(m_loader, m_loaderVersion->descriptor());

        inst.setName(name());
        inst.setIconKey(m_instIcon);
    }
    instanceSettings->resumeSave();

    emitSucceeded();
}

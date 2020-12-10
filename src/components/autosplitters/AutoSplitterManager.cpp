#include "AutoSplitterManager.h"
#include "Dribble2OverhaulAutoSplitter.h"

AutoSplitterManager &AutoSplitterManager::getInstance(BakkesMod::Plugin::BakkesModPlugin *plugin)
{
    static AutoSplitterManager instance(plugin);
    return instance;
}

AutoSplitterManager::AutoSplitterManager(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : plugin(plugin), autoSplitters(), previousMapName()
{
    auto splitters = std::vector<std::shared_ptr<AutoSplitter>>();
    splitters.push_back(std::make_shared<Dribble2OverhaulAutoSplitter>(plugin));

    for (auto &splitter : splitters)
    {
        auto mapName = splitter->mapName();
        this->autoSplitters[mapName] = splitter;
    }
}

std::shared_ptr<AutoSplitter> AutoSplitterManager::getAutoSplitterForCurrentMap()
{
    if (!this->plugin->gameWrapper->IsInGame()) return nullptr;

    std::string currentMapName = this->plugin->gameWrapper->GetCurrentMap();

    auto splitter = this->autoSplitters.find(currentMapName);
    if (splitter == this->autoSplitters.end()) return nullptr;

    auto currentAutoSplitter = this->autoSplitters[currentMapName];

    if (currentMapName != previousMapName)
    {
        currentAutoSplitter->reset();
    }
    this->previousMapName = currentMapName;

    return currentAutoSplitter;
}

bool AutoSplitterManager::isCurrentMapSupported()
{
    return this->getAutoSplitterForCurrentMap() != nullptr;
}

bool AutoSplitterManager::update()
{
    auto currentAutoSplitter = this->getAutoSplitterForCurrentMap();
    if (currentAutoSplitter == nullptr) return false;

    return currentAutoSplitter->update();
}

bool AutoSplitterManager::shouldStartTimer()
{
    auto currentAutoSplitter = this->getAutoSplitterForCurrentMap();
    if (currentAutoSplitter == nullptr) return false;

    return currentAutoSplitter->shouldStartTimer();
}

bool AutoSplitterManager::shouldSplitTimer()
{
    auto currentAutoSplitter = this->getAutoSplitterForCurrentMap();
    if (currentAutoSplitter == nullptr) return false;

    return currentAutoSplitter->shouldSplitTimer();
}

bool AutoSplitterManager::shouldResetTimer()
{
    auto currentAutoSplitter = this->getAutoSplitterForCurrentMap();
    if (currentAutoSplitter == nullptr) return false;

    return currentAutoSplitter->shouldResetTimer();
}

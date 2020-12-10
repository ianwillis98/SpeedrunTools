#pragma once

#include <bakkesmod/plugin/bakkesmodplugin.h>
#include "AutoSplitter.h"

class AutoSplitterManager
{
private:
    BakkesMod::Plugin::BakkesModPlugin *plugin;
    std::map<std::string, std::shared_ptr<AutoSplitter>> autoSplitters;
    std::string previousMapName;

    explicit AutoSplitterManager(BakkesMod::Plugin::BakkesModPlugin *plugin);

    std::shared_ptr<AutoSplitter> getAutoSplitterForCurrentMap();

public:
    static AutoSplitterManager &getInstance(BakkesMod::Plugin::BakkesModPlugin *plugin);

    bool isCurrentMapSupported();

    bool update();
    bool shouldStartTimer();
    bool shouldSplitTimer();
    bool shouldResetTimer();
};

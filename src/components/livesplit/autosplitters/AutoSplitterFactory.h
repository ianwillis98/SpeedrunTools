#pragma once

#include <bakkesmod/plugin/bakkesmodplugin.h>
#include "AutoSplitter.h"

class AutoSplitterFactory
{
private:
    BakkesMod::Plugin::BakkesModPlugin *plugin;
    explicit AutoSplitterFactory(BakkesMod::Plugin::BakkesModPlugin *plugin);

public:
    static AutoSplitterFactory &getInstance(BakkesMod::Plugin::BakkesModPlugin *plugin);

    std::unique_ptr<AutoSplitter> getAutoSplitterForRun(const std::string &runName);
};

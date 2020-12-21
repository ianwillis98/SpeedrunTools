#pragma once

#include <bakkesmod/plugin/bakkesmodplugin.h>
#include "../AutoSplitter.h"

class AutoSplitterFactory
{
private:
    BakkesMod::Plugin::BakkesModPlugin *plugin;

    explicit AutoSplitterFactory(BakkesMod::Plugin::BakkesModPlugin *plugin);

public:
    static AutoSplitterFactory &getInstance(BakkesMod::Plugin::BakkesModPlugin *plugin);

    std::unique_ptr<AutoSplitter> getAutoSplitterForMap(const std::string &mapName);
};

class AutoSplitterMap
{
public:
    static const AutoSplitterMap Null;
    static const AutoSplitterMap Dribble2Overhaul;
    static const AutoSplitterMap TutorialBasic;

    static const std::vector<AutoSplitterMap> maps;
    static const char *mapTitles[];
    static const char *mapNames[];

private:
    AutoSplitterMap(std::string mapTitle, std::string mapName);

public:
    const std::string mapTitle;
    const std::string mapName;
};

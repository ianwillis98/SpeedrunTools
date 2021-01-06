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

    std::unique_ptr<AutoSplitter> getAutoSplitterForRun(const std::string &runTitle);
};

class AutoSplitterRunTemp
{
public:
    static const AutoSplitterRunTemp Null;
    static const AutoSplitterRunTemp Dribble2Overhaul;
    static const AutoSplitterRunTemp TutorialBasic;
    static const AutoSplitterRunTemp TutorialAdvanced;
    static const AutoSplitterRunTemp SpeedJumpRings1_100;

    static const std::vector<AutoSplitterRunTemp> runs;
    static const char *runNames[];

private:
    explicit AutoSplitterRunTemp(std::string runName);

public:
    const std::string runName;
};

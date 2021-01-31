#pragma once

#include <string>

class AutoSplitterSupportedRun
{
public:
    static const AutoSplitterSupportedRun NONE;
    static const AutoSplitterSupportedRun TUTORIAL_BASIC;
    static const AutoSplitterSupportedRun TUTORIAL_ADVANCED;
    static const AutoSplitterSupportedRun PANICS_AIR_RACE_BEACH;
    static const AutoSplitterSupportedRun AIR_DRIBBLE_HOOPS;
    static const AutoSplitterSupportedRun LETHS_GIANT_RINGS;
    static const AutoSplitterSupportedRun SPEED_JUMP_RINGS_1;
    static const AutoSplitterSupportedRun SPEED_JUMP_TRIALS_1;

public:
    const std::string runName;

private:
    explicit AutoSplitterSupportedRun(std::string runName);
};


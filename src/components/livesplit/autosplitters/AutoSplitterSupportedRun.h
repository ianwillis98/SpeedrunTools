#pragma once

#include <string>

class AutoSplitterSupportedRun
{
public:
    static const AutoSplitterSupportedRun NONE;
    static const AutoSplitterSupportedRun TUTORIAL_BASIC;
    static const AutoSplitterSupportedRun TUTORIAL_ADVANCED;
    static const AutoSplitterSupportedRun PANICS_AIR_RACE_BEACH;
    static const AutoSplitterSupportedRun SPEED_JUMP_RINGS_1;
    static const AutoSplitterSupportedRun AIR_DRIBBLE_HOOPS;
    static const AutoSplitterSupportedRun LETHS_GIANT_RINGS;

public:
    const std::string runName;

private:
    explicit AutoSplitterSupportedRun(std::string runName);
};


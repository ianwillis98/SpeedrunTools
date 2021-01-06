#pragma once

#include <string>

class AutoSplitterSupportedRun
{
public:
    static const AutoSplitterSupportedRun NONE;
    static const AutoSplitterSupportedRun TUTORIAL_BASIC;
    static const AutoSplitterSupportedRun TUTORIAL_ADVANCED;
    static const AutoSplitterSupportedRun PANICS_AIR_RACE_BEACH;

public:
    const std::string runName;

private:
    explicit AutoSplitterSupportedRun(std::string runName);
};


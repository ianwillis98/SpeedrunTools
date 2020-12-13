#pragma once

#include <sstream>
#include <map>
#include <bakkesmod/plugin/bakkesmodplugin.h>
#include <bakkesmod/wrappers/kismet/SequenceWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceVariableWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceOpWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceObjectWrapper.h>

class AutoSplitter
{
public:
    virtual bool update() = 0;

    virtual bool shouldTimerStart() = 0;
    virtual bool shouldTimerSplit() = 0;
    virtual bool shouldTimerReset() = 0;
};

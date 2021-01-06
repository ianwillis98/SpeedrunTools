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
    virtual void onEvent(const std::string &eventName, bool post, void *params) = 0;

    virtual bool supportsAutoStart() = 0;
    virtual bool supportsAutoSplit() = 0;
    virtual bool supportsAutoReset() = 0;

    virtual bool shouldTimerStart() = 0;
    virtual bool shouldTimerSplit() = 0;
    virtual bool shouldTimerReset() = 0;

    virtual std::string getDebug() = 0;

    virtual std::string autoStartDescription() = 0;
    virtual std::string autoSplitDescription() = 0;
    virtual std::string autoResetDescription() = 0;
};

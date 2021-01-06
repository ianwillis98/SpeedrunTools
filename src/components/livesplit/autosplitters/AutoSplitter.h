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
    virtual void onEvent(const std::string &eventName, bool post, void *params) = 0;

    virtual bool start() = 0;
    virtual bool split() = 0;
    virtual bool reset() = 0;

    virtual bool supportsStart() = 0;
    virtual bool supportsSplit() = 0;
    virtual bool supportsReset() = 0;

    virtual std::string startDescription() = 0;
    virtual std::string splitDescription() = 0;
    virtual std::string resetDescription() = 0;

    virtual std::string getDebug() = 0;
};

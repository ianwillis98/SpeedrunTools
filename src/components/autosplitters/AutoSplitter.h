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
protected:
    BakkesMod::Plugin::BakkesModPlugin *plugin;

public:
    explicit AutoSplitter(BakkesMod::Plugin::BakkesModPlugin *plugin) : plugin(plugin)
    {}

    virtual std::string mapName()
    {
        return "";
    }

    virtual void reset()
    {

    }

    virtual bool update()
    {
        return true;
    }

    virtual bool shouldStartTimer()
    {
        return false;
    }

    virtual bool shouldSplitTimer()
    {
        return false;
    }

    virtual bool shouldResetTimer()
    {
        return false;
    }
};

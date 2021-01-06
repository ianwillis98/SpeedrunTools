#include "AutoSplitterBase.h"

AutoSplitterBase::AutoSplitterBase(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : plugin(plugin),
          shouldTimerStart(false),
          shouldTimerSplit(false),
          shouldTimerReset(false)
{

}

void AutoSplitterBase::onEvent(const std::string &eventName, bool post, void *params)
{
    this->shouldTimerStart = false;
    this->shouldTimerSplit = false;
    this->shouldTimerReset = false;
    this->onEventReceived(eventName, post, params);
}

bool AutoSplitterBase::start()
{
    return this->shouldTimerStart;
}

bool AutoSplitterBase::split()
{
    return this->shouldTimerSplit;
}

bool AutoSplitterBase::reset()
{
    return this->shouldTimerReset;
}

bool AutoSplitterBase::supportsStart()
{
    return true;
}

bool AutoSplitterBase::supportsSplit()
{
    return true;
}

bool AutoSplitterBase::supportsReset()
{
    return true;
}

std::string AutoSplitterBase::startDescription()
{
    return std::string();
}

std::string AutoSplitterBase::splitDescription()
{
    return std::string();
}

std::string AutoSplitterBase::resetDescription()
{
    return std::string();
}

std::string AutoSplitterBase::getDebug()
{
    return std::string();
}
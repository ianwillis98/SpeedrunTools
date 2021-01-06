#include "AutoSplitterBase.h"

AutoSplitterBase::AutoSplitterBase(BakkesMod::Plugin::BakkesModPlugin *plugin) : plugin(plugin)
{

}

bool AutoSplitterBase::update()
{
    return true;
}

void AutoSplitterBase::onEvent(const std::string &eventName, bool post, void *params)
{

}

bool AutoSplitterBase::supportsAutoStart()
{
    return false;
}

bool AutoSplitterBase::supportsAutoSplit()
{
    return false;
}

bool AutoSplitterBase::supportsAutoReset()
{
    return false;
}

bool AutoSplitterBase::shouldTimerStart()
{
    return false;
}

bool AutoSplitterBase::shouldTimerSplit()
{
    return false;
}

bool AutoSplitterBase::shouldTimerReset()
{
    return false;
}

std::string AutoSplitterBase::getDebug()
{
    return std::string();
}

std::string AutoSplitterBase::autoStartDescription()
{
    return std::string();
}

std::string AutoSplitterBase::autoSplitDescription()
{
    return std::string();
}

std::string AutoSplitterBase::autoResetDescription()
{
    return std::string();
}

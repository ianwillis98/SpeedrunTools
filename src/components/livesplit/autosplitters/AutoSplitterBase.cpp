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

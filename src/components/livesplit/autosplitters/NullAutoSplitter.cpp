#include "NullAutoSplitter.h"

bool NullAutoSplitter::update()
{
    return false;
}

void NullAutoSplitter::onEvent(const std::string &eventName, bool post, void *params)
{

}

bool NullAutoSplitter::shouldTimerStart()
{
    return false;
}

bool NullAutoSplitter::shouldTimerSplit()
{
    return false;
}

bool NullAutoSplitter::shouldTimerReset()
{
    return false;
}

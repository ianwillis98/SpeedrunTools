#pragma once

#include "../AutoSplitter.h"

class NullAutoSplitter : public AutoSplitter
{
public:
    bool update() override;
    void onEvent(const std::string &eventName, bool post, void *params) override;

    bool shouldTimerStart() override;
    bool shouldTimerSplit() override;
    bool shouldTimerReset() override;
};

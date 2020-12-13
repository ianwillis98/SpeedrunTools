#pragma once

#include "AutoSplitter.h"

class AutoSplitterNull : public AutoSplitter
{
    bool update() override;

    bool shouldTimerStart() override;
    bool shouldTimerSplit() override;
    bool shouldTimerReset() override;
};

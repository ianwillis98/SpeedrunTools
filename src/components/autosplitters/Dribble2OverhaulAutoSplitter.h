#pragma once

#include "AutoSplitterBase.h"

class Dribble2OverhaulAutoSplitter : public AutoSplitterBase
{
private:
    bool hasUpdatedOnce;
    bool hasUpdatedTwice;

    bool previousTiming;
    int previousLevel;

    bool currentTiming;
    int currentLevel;

public:
    explicit Dribble2OverhaulAutoSplitter(BakkesMod::Plugin::BakkesModPlugin *plugin);

    bool update() override;

    bool shouldTimerStart() override;
    bool shouldTimerSplit() override;
    bool shouldTimerReset() override;
};

#pragma once

#include "AutoSplitter.h"

class Dribble2OverhaulAutoSplitter : public AutoSplitter
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

    std::string mapName() override;

    void reset() override;
    bool update() override;

    bool shouldStartTimer() override;
    bool shouldSplitTimer() override;
};

#pragma once

#include "../AutoSplitterBase.h"

class SpeedJumpTrials1AutoSplitter : public AutoSplitterBase
{
private:
    bool hasUpdatedOnce;
    bool hasUpdatedTwice;

    int currentLevel;
    int previousLevel;

    int currentMin;

    int currentSec;
    int previousSec;

    bool currentReset;

public:
    explicit SpeedJumpTrials1AutoSplitter(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onEventReceived(const std::string &eventName, bool post, void *params) override;

    std::string startDescription() override;
    std::string splitDescription() override;
    std::string resetDescription() override;

    std::string getDebug() override;
};

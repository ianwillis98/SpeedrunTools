#pragma once

#include "../AutoSplitterBase.h"

class SpeedJumpRings1AutoSplitter : public AutoSplitterBase
{
private:
    bool hasUpdatedOnce;
    bool hasUpdatedTwice;

    int currentRings;
    int previousRings;

public:
    explicit SpeedJumpRings1AutoSplitter(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onEventReceived(const std::string &eventName, bool post, void *params) override;

    std::string startDescription() override;
    std::string splitDescription() override;
    std::string resetDescription() override;

    std::string getDebug() override;

private:
    void resetRingsKismetToZero();
};

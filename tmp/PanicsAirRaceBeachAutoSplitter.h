#pragma once

#include "../AutoSplitterBase.h"

class PanicsAirRaceBeachAutoSplitter : public AutoSplitterBase
{
private:
    bool hasUpdatedOnce;
    bool hasUpdatedTwice;

    int previousRings;
    int currentRings;

    int previousCheckpoint;
    int currentCheckpoint;

public:
    explicit PanicsAirRaceBeachAutoSplitter(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onEventReceived(const std::string &eventName, bool post, void *params) override;

    std::string startDescription() override;
    std::string splitDescription() override;
    std::string resetDescription() override;

    std::string getDebug() override;
};

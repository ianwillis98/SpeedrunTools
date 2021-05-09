#pragma once

#include "../AutoSplitterComponent.h"

class PanicsAirRaceBeachAutoSplitterComponent : public AutoSplitterComponent
{
private:
    bool hasUpdatedOnce;
    bool hasUpdatedTwice;

    int currentRings;
    int previousRings;

    int currentCheckpoint;
    int previousCheckpoint;

public:
    explicit PanicsAirRaceBeachAutoSplitterComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

protected:
    void update(const std::string &eventName, bool post, void *params) override;

    std::string getStartDescription() override;
    std::string getSplitDescription() override;
    std::string getResetDescription() override;
    std::string getDebugText() override;
};

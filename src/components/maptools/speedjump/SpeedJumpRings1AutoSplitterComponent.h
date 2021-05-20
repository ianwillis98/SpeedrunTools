#pragma once

#include "../AutoSplitterComponent.h"

class SpeedJumpRings1AutoSplitterComponent : public AutoSplitterComponent
{
private:
    bool hasUpdatedOnce;
    bool hasUpdatedTwice;

    int currentRings;
    int previousRings;

public:
    explicit SpeedJumpRings1AutoSplitterComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onEnable() override;
    void update(const std::string &eventName, bool post, void *params) override;

    std::string getStartDescription() override;
    std::string getSplitDescription() override;
    std::string getResetDescription() override;
    std::string getDebugText() override;

private:
    void resetRingsKismetToZero();
};

#pragma once

#include "../../AutoSplitterComponent.h"

class SpeedJumpTrials1AutoSplitterComponent : public AutoSplitterComponent
{
private:
    int level;
    bool resetMap;

public:
    explicit SpeedJumpTrials1AutoSplitterComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onEnable() override;
    void update(const std::string &eventName, bool post, void *params) override;

    std::string getStartDescription() override;
    std::string getSplitDescription() override;
    std::string getResetDescription() override;
    std::string getDebugText() override;
};

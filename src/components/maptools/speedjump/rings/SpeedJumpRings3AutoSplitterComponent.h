#pragma once

#include "../../AutoSplitterComponent.h"

class SpeedJumpRings3AutoSplitterComponent : public AutoSplitterComponent
{
private:
    std::string timer;
    int level;

public:
    explicit SpeedJumpRings3AutoSplitterComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onEnable() override;
    void update(const std::string &eventName, bool post, void *params) override;

    std::string getStartDescription() override;
    std::string getSplitDescription() override;
    std::string getResetDescription() override;
    std::string getDebugText() override;
};

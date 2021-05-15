#pragma once

#include "../../AutoSplitterComponent.h"

class SpeedJumpRings2AutoSplitterComponent : public AutoSplitterComponent
{
private:
    bool hasUpdatedOnce;
    bool hasUpdatedTwice;

    int currentLevel;
    int previousLevel;

    std::string currentDisplayTimer;
    std::string previousDisplayTimer;

public:
    explicit SpeedJumpRings2AutoSplitterComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onEnable() override;
    void update(const std::string &eventName, bool post, void *params) override;

    std::string getStartDescription() override;
    std::string getSplitDescription() override;
    std::string getResetDescription() override;
    std::string getDebugText() override;
};

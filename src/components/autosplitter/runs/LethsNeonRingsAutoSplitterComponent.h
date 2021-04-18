#pragma once

#include "../../../services/LiveSplitClient.h"
#include "../AutoSplitterComponent.h"

class LethsNeonRingsAutoSplitterComponent : public AutoSplitterComponent
{
private:
    bool hasUpdatedOnce;
    bool hasUpdatedTwice;

    int currentLevel;
    int previousLevel;

    bool currentTiming;
    bool previousTiming;

public:
    explicit LethsNeonRingsAutoSplitterComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

protected:
    void update(const std::string &eventName, bool post, void *params) override;

    std::string getDebugText() override;
};

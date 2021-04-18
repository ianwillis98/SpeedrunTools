#pragma once

#include "../../../autosplitter/AutoSplitterBase.h"

class LethsGiantRingsAutoSplitter : public AutoSplitterBase
{
private:
    bool hasUpdatedOnce{};
    bool hasUpdatedTwice{};

    bool currentTiming;
    bool previousTiming;

    int currentLevel;
    int previousLevel;

public:
    explicit LethsGiantRingsAutoSplitter(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onEventReceived(const std::string &eventName, bool post, void *params) override;

    bool supportsReset() override;

    std::string startDescription() override;
    std::string splitDescription() override;
    std::string resetDescription() override;

    std::string getDebug() override;
};

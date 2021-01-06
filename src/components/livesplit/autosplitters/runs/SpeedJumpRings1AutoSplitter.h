#pragma once

#include "../AutoSplitterBase.h"

class SpeedJumpRings1AutoSplitter : public AutoSplitterBase
{
private:
    bool hasUpdatedOnce;
    bool hasUpdatedTwice;

    int previousRings;
    int currentRings;

    bool shouldStartTimer;
    bool shouldSplitTimer;
    bool shouldResetTimer;

public:
    explicit SpeedJumpRings1AutoSplitter(BakkesMod::Plugin::BakkesModPlugin *plugin);

    bool update() override;
    void onEvent(const std::string &eventName, bool post, void *params) override;

    bool supportsAutoStart() override;
    bool supportsAutoSplit() override;
    bool supportsAutoReset() override;

    bool shouldTimerStart() override;
    bool shouldTimerSplit() override;
    bool shouldTimerReset() override;

    std::string getDebug() override;

    std::string autoStartDescription() override;
    std::string autoSplitDescription() override;
    std::string autoResetDescription() override;
};

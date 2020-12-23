#pragma once

#include "AutoSplitterBase.h"

class TutorialBasicAutoSplitter : public AutoSplitterBase
{
private:
    bool shouldStartTimer;
    bool shouldSplitTimer;
    bool shouldResetTimer;
    int level;

public:
    explicit TutorialBasicAutoSplitter(BakkesMod::Plugin::BakkesModPlugin *plugin);

    bool update() override;
    void onEvent(const std::string &eventName, bool post, void *params) override;

    bool shouldTimerStart() override;
    bool shouldTimerSplit() override;
    bool shouldTimerReset() override;
};

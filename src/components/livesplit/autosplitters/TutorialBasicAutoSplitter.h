#pragma once

#include "AutoSplitterBase.h"

class TutorialBasicAutoSplitter : public AutoSplitterBase
{
private:
    bool isInTutorial;
    bool shouldStartTimer;
    bool shouldSplitTimer;
    bool shouldResetTimer;
    int segment;

public:
    explicit TutorialBasicAutoSplitter(BakkesMod::Plugin::BakkesModPlugin *plugin);

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

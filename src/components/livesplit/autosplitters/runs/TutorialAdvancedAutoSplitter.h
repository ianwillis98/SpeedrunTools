#pragma once

#include "../AutoSplitterBase.h"

class TutorialAdvancedAutoSplitter : public AutoSplitterBase
{
private:
    bool isInTutorial;
    bool shouldStartTimer;
    bool shouldSplitTimer;
    bool shouldResetTimer;
    int segment;
    int segment4GoalsScored;
    int segment5GoalsScored;

public:
    explicit TutorialAdvancedAutoSplitter(BakkesMod::Plugin::BakkesModPlugin *plugin);

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

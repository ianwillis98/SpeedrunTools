#pragma once

#include "../AutoSplitterBase.h"

class TutorialAdvancedAutoSplitter : public AutoSplitterBase
{
private:
    bool isInTutorial;
    int segment;
    int segment4GoalsScored;
    int segment5GoalsScored;

public:
    explicit TutorialAdvancedAutoSplitter(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onEventReceived(const std::string &eventName, bool post, void *params) override;

    std::string startDescription() override;
    std::string splitDescription() override;
    std::string resetDescription() override;

    std::string getDebug() override;
};

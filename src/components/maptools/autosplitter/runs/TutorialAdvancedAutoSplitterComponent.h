#pragma once

#include "../AutoSplitterComponent.h"

class TutorialAdvancedAutoSplitterComponent : public AutoSplitterComponent
{
private:
    bool isInTutorial;
    int segment;
    int segment4GoalsScored;
    int segment5GoalsScored;
public:
    explicit TutorialAdvancedAutoSplitterComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

protected:
    void update(const std::string &eventName, bool post, void *params) override;

    std::string getStartDescription() override;
    std::string getSplitDescription() override;
    std::string getResetDescription() override;
    std::string getDebugText() override;
};

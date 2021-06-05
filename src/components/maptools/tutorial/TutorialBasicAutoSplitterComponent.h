#pragma once

#include "../AutoSplitterComponent.h"

class TutorialBasicAutoSplitterComponent : public AutoSplitterComponent
{
private:
    bool isInTutorial;

public:
    explicit TutorialBasicAutoSplitterComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

protected:
    void update(const std::string &eventName, bool post, void *params) override;

    std::string getStartDescription() override;
    std::string getSplitDescription() override;
    std::string getResetDescription() override;
    std::string getDebugText() override;
};

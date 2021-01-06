#pragma once

#include "../AutoSplitterBase.h"

class TutorialBasicAutoSplitter : public AutoSplitterBase
{
private:
    bool isInTutorial;
    int segment;

public:
    explicit TutorialBasicAutoSplitter(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onEventReceived(const std::string &eventName, bool post, void *params) override;

    std::string startDescription() override;
    std::string splitDescription() override;
    std::string resetDescription() override;

    std::string getDebug() override;
};

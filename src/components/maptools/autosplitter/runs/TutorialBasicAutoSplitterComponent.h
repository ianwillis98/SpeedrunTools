#pragma once

#include "../AutoSplitterComponent.h"

class TutorialBasicAutoSplitterComponent : public AutoSplitterComponent
{
private:
    bool isInTutorial;
    int segment;

public:
    explicit TutorialBasicAutoSplitterComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);


protected:
    void update(const std::string &eventName, bool post, void *params) override;

    std::string getDebugText() override;
};

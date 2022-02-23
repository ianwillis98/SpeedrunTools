#pragma once

#include "../../AutoSplitterComponent.h"

class SpeedJumpRings1AutoSplitterComponent : public AutoSplitterComponent
{
private:
    int rings;

public:
    explicit SpeedJumpRings1AutoSplitterComponent(NetcodePlugin *plugin);

    void onEnable() override;
    void update(const std::string &eventName, bool post, void *params) override;

    std::string getStartDescription() override;
    std::string getSplitDescription() override;
    std::string getResetDescription() override;
    std::string getDebugText() override;
};

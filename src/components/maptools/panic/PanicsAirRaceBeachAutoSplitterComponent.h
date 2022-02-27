#pragma once

#include "../AutoSplitterComponent.h"

class PanicsAirRaceBeachAutoSplitterComponent : public AutoSplitterComponent
{
private:
    int rings;
    int checkpoint;

public:
    explicit PanicsAirRaceBeachAutoSplitterComponent(NetcodePlugin *plugin);

protected:
    void onEnable() override;
    void update(const std::string &eventName, bool post, void *params) override;

    std::string getStartDescription() override;
    std::string getSplitDescription() override;
    std::string getResetDescription() override;
    std::string getDebugText() override;
};
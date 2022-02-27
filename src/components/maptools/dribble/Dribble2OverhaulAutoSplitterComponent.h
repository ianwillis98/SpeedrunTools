#pragma once

#include "../AutoSplitterComponent.h"

class Dribble2OverhaulAutoSplitterComponent : public AutoSplitterComponent
{
private:
    int checkpoint;
    bool timing;

public:
    explicit Dribble2OverhaulAutoSplitterComponent(NetcodePlugin* plugin);

protected:
    void onEnable() override;
    void update(const std::string& eventName, bool post, void* params) override;

    std::string getStartDescription() override;
    std::string getSplitDescription() override;
    std::string getResetDescription() override;
    std::string getDebugText() override;
};
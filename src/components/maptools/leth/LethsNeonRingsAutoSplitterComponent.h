#pragma once

#include "../AutoSplitterComponent.h"
#include "../../../services/LiveSplitClient.h"

class LethsNeonRingsAutoSplitterComponent : public AutoSplitterComponent
{
private:
    bool timing;
    int level;

public:
    explicit LethsNeonRingsAutoSplitterComponent(NetcodePlugin *plugin);

protected:
    void onEnable() override;
    void update(const std::string &eventName, bool post, void *params) override;

    std::string getStartDescription() override;
    std::string getSplitDescription() override;
    std::string getResetDescription() override;
    std::string getDebugText() override;
};

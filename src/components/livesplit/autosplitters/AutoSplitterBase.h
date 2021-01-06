#pragma once

#include <bakkesmod/plugin/bakkesmodplugin.h>
#include "AutoSplitter.h"

class AutoSplitterBase : public AutoSplitter
{
protected:
    BakkesMod::Plugin::BakkesModPlugin *plugin;

public:
    explicit AutoSplitterBase(BakkesMod::Plugin::BakkesModPlugin *plugin);

    bool update() override;
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

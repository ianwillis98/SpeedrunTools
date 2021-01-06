#pragma once

#include <bakkesmod/plugin/bakkesmodplugin.h>
#include "AutoSplitter.h"

class AutoSplitterBase : public AutoSplitter
{
protected:
    BakkesMod::Plugin::BakkesModPlugin *plugin;
    bool shouldTimerStart;
    bool shouldTimerSplit;
    bool shouldTimerReset;

public:
    explicit AutoSplitterBase(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onEvent(const std::string &eventName, bool post, void *params) final;
    virtual void onEventReceived(const std::string &eventName, bool post, void *params) = 0;

    bool start() final;
    bool split() final;
    bool reset() final;

    bool supportsStart() override;
    bool supportsSplit() override;
    bool supportsReset() override;

    std::string startDescription() override;
    std::string splitDescription() override;
    std::string resetDescription() override;

    std::string getDebug() override;
};

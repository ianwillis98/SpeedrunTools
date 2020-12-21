#pragma once

#include "../PluginToolkitBase.h"
#include "../../components/livesplit/LiveSplitRemoteComponent.h"
#include "../../components/livesplit/AutoSplitterComponent.h"

class LiveSplitToolkit : public PluginToolkitBase
{
private:
    LiveSplitRemoteComponent liveSplitRemoteComponent;
    AutoSplitterComponent autoSplitterComponent;

public:
    explicit LiveSplitToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin);

    std::string title() override;
    void onLoad() override;
    void render() override;
    void onEvent(const std::string &eventName, bool post, void *params) override;
};

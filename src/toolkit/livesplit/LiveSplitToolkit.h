#pragma once

#include "../PluginToolkit.h"
#include "../../component/livesplit/LiveSplitComponent.h"

class LiveSplitToolkit : public PluginToolkit
{
private:
    LiveSplitComponent liveSplitComponent;

public:
    explicit LiveSplitToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin);

    std::string title() override;
    void onLoad() override;
    void onUnload() override;
    void render() override;
};

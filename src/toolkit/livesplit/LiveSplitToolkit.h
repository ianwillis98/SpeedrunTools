#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "../PluginToolkit.h"
#include "../../components/livesplit/LiveSplitComponent.h"

class LiveSplitToolkit : public PluginToolkit
{
public:
    explicit LiveSplitToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin);

    std::string title() override;
    void onLoad() override;
    void onUnload() override;
    void render() override;

private:
    LiveSplitComponent liveSplitComponent;
};

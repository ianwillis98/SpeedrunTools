#pragma once

#include "../PluginView.h"

class LiveSplitFullView : public PluginView
{
public:
    explicit LiveSplitFullView(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void render() override;
};

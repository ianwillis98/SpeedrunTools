#pragma once

#include "../PluginComponent.h"

class AutoAirRollComponent : public PluginComponent
{
public:
    explicit AutoAirRollComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onLoad() override;
    void onUnload() override;
    void render() override;
};

#pragma once

#include "../../../plugin/PluginComponent.h"

class PanicsAirRaceBeachComponent : public PluginComponent
{
public:
    explicit PanicsAirRaceBeachComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onLoad() override;
    void onUnload() override;
    void render() override;

    bool isComponentEnabled();
    void setComponentEnabled(bool enabled);

private:
    void onComponentEnabledChanged();
};

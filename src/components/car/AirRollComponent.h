#pragma once

#include "../../plugin/PluginComponent.h"

class AirRollComponent : public PluginComponent
{
public:
    explicit AirRollComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onLoad() override;
    void onUnload() override;
    void render() override;

    bool isComponentEnabled();
    void setComponentEnabled(bool enabled);

private:
    void onComponentEnabledChanged();
};

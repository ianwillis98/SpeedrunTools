#pragma once

#include "../PluginComponent.h"

class AutoAirRollComponent : public PluginComponent
{
public:
    enum AirRollMutator
    {
        None,
        DisableAirRoll,
        AutoAirRollLeft,
        AutoAirRollRight,
    };

private:
    AirRollMutator mutator;

public:
    explicit AutoAirRollComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onLoad() override;
    void onUnload() override;
    void render() override;

    AirRollMutator getAirRollMutator();
    void setAirRollMutator(AirRollMutator m);

private:
    void onPhysicsTick();
    void setAirRollAmount(float amount);
};

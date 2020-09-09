#pragma once

#include "../PluginComponent.h"

class AutoAirRollComponent : public PluginComponent
{
public:
    enum AirRollMutator
    {
        None = 0,
        DisableAirRoll = 1,
        AutoAirRollLeft = 2,
        AutoAirRollRight = 3,
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

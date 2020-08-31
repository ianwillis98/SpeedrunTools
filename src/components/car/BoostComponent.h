#pragma once

#include "../../plugin/PluginComponent.h"

enum BoostMutator {
    None = 0,
    Unlimited = 1,
    Zero = 2
};

class BoostComponent : public PluginComponent
{
public:
    explicit BoostComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onLoad() override;
    void onUnload() override;
    void render() override;

    BoostMutator getBoostMutator();
    void setBoostMutator(BoostMutator mutator);

private:
    void onPhysicsTick();
    void setBoostAmount(float amount);

    void onBoostMutatorChanged();
};

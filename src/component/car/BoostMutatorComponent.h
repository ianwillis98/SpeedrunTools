#pragma once

#include "../PluginComponent.h"

enum BoostMutator
{
    None,
    Unlimited,
    Zero
};

class BoostMutatorComponent : public PluginComponent
{
private:
    BoostMutator boostMutator;

public:
    explicit BoostMutatorComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onLoad() override;
    void onUnload() override;
    void render() override;

    BoostMutator getBoostMutator();
    void setBoostMutator(BoostMutator mutator);

private:
    void onPhysicsTick();
    void setBoostAmount(float amount);
};

#pragma once

#include "../PluginComponent.h"

class BoostMutatorComponent : public PluginComponent
{
public:
    enum BoostMutator
    {
        None = 0,
        Zero = 1,
        Unlimited = 2,
    };

private:
    BoostMutator mutator;

public:
    explicit BoostMutatorComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onLoad() override;
    void onUnload() override;
    void render() override;

    BoostMutator getBoostMutator();
    void setBoostMutator(BoostMutator m);

private:
    void onPhysicsTick();
    void setBoostAmount(float amount);
};

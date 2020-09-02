#pragma once

#include "../PluginComponent.h"
#include "../../models/CarState.h"

class CarAnalysisComponent : public PluginComponent
{
private:
    CarState currentCarState;

public:
    explicit CarAnalysisComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onLoad() override;
    void onUnload() override;
    void render() override;

private:
    void onPhysicsTick();
};

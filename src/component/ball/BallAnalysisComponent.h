#pragma once

#include "../PluginComponent.h"
#include "../../models/BallState.h"

class BallAnalysisComponent : public PluginComponent
{
private:
    BallState currentBallState;

public:
    explicit BallAnalysisComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onLoad() override;
    void onUnload() override;
    void render() override;

private:
    void onPhysicsTick();
};

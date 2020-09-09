#pragma once

#include "../PluginToolkit.h"
#include "../../component/game/GameGravityComponent.h"
#include "../../component/game/GameSpeedComponent.h"
#include "../../component/car/BoostMutatorComponent.h"
#include "../../component/car/AutoAirRollComponent.h"

class MutatorsToolkit : public PluginToolkit
{
private:
    GameGravityComponent gameGravityComponent;
    GameSpeedComponent gameSpeedComponent;
    BoostMutatorComponent boostMutatorComponent;
    AutoAirRollComponent autoAirRollComponent;

public:
    explicit MutatorsToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin);

    std::string title() override;
    void onLoad() override;
    void onUnload() override;
    void render() override;

private:
    void createGameGravityCVar();
    void createGameSpeedCVar();
    void createBoostMutatorCVar();
    void createAutoAirRollMutator();
};

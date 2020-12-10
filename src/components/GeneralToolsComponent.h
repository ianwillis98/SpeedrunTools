#pragma once

#include "../PluginComponent.h"
#include "../models/GameState.h"

enum class BoostMutator
{
    None = 0,
    ZeroBoost = 1,
    UnlimitedBoost = 2,
};

enum class AirRollMutator
{
    None = 0,
    DisableAirRoll = 1,
    AutoAirRollLeft = 2,
    AutoAirRollRight = 3,
};

class GeneralToolsComponent : public PluginComponent
{
private:
    GameState currentGameState;
    BoostMutator boostMutator;
    AirRollMutator airRollMutator;


public:
    explicit GeneralToolsComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    std::string title() override;
    void onLoad() override;
    void render() override;
    void onEvent(std::string eventName, bool post, void *params) override;

private:
    void setBoostAmount(float amount);

    void createBoostMutatorCVar();
    void createAirRollMutatorCVar();
    void createGameGravityMutatorCVar();
    void createGameSpeedMutatorCVar();

    void renderCurrentGameState();
    void renderBoostMutator();
    void renderAirRollMutator();
    void renderGameGravityMutator();
    void renderGameSpeedMutator();
};

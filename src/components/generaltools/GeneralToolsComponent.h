#pragma once

#include "../PluginComponentBase.h"
#include "../../models/GameState.h"

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
    ForceAirRollLeft = 2,
    ForceAirRollRight = 3,
};

class GeneralToolsComponent : public PluginComponentBase
{
public:
    static const std::string AirRollMutatorCVarName;
    static const std::string BoostMutatorCVarName;
    static const std::string GameGravityMutatorCVarName;
    static const std::string GameSpeedMutatorCVarName;

private:
    GameState currentGameState;
    BoostMutator boostMutator;
    AirRollMutator airRollMutator;

public:
    explicit GeneralToolsComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onLoad() override;
    void render() override;
    void onEvent(const std::string &eventName, bool post, void *params) override;

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

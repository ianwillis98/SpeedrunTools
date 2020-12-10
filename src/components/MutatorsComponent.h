//#pragma once
//
//#include "../PluginComponent.h"
//
//enum class BoostMutator
//{
//    None = 0,
//    ZeroBoost = 1,
//    UnlimitedBoost = 2,
//};
//
//enum class AirRollMutator
//{
//    None = 0,
//    DisableAirRoll = 1,
//    AutoAirRollLeft = 2,
//    AutoAirRollRight = 3,
//};
//
//class MutatorsComponent : public PluginComponent
//{
//private:
//    BoostMutator boostMutator;
//    AirRollMutator airRollMutator;
//
//public:
//    explicit MutatorsComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);
//
//    std::string title() override;
//    void onLoad() override;
//    void render() override;
//    void onEvent(std::string eventName, bool post, void *params) override;
//
//private:
//    void setBoostAmount(float amount);
//
//    void createBoostMutatorCVar();
//    void createAirRollMutatorCVar();
//    void createGameGravityMutatorCVar();
//    void createGameSpeedMutatorCVar();
//
//    void renderBoostMutator();
//    void renderAirRollMutator();
//    void renderGameGravityMutator();
//    void renderGameSpeedMutator();
//};

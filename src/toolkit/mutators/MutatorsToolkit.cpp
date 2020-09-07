#include "MutatorsToolkit.h"

MutatorsToolkit::MutatorsToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginToolkit(plugin), gameGravityComponent(plugin), gameSpeedComponent(plugin), boostMutatorComponent(plugin), autoAirRollComponent(plugin)
{

}

std::string MutatorsToolkit::title()
{
    return "Mutators";
}

void MutatorsToolkit::onLoad()
{
    this->gameGravityComponent.onLoad();
    this->gameSpeedComponent.onLoad();
    this->boostMutatorComponent.onLoad();
    this->autoAirRollComponent.onLoad();

    this->createGameGravityCVar();
    this->createGameSpeedCVar();
    this->createBoostMutatorCVar();
}

void MutatorsToolkit::onUnload()
{
    this->gameGravityComponent.onUnload();
    this->gameSpeedComponent.onUnload();
    this->boostMutatorComponent.onUnload();
    this->autoAirRollComponent.onUnload();
}

void MutatorsToolkit::render()
{
    ImGui::Spacing();

    this->boostMutatorComponent.render();

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    this->gameGravityComponent.render();

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    this->gameSpeedComponent.render();

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    this->autoAirRollComponent.render();

    ImGui::Spacing();
}

void MutatorsToolkit::createGameGravityCVar()
{
    std::string currentGameGravity = this->plugin->cvarManager->getCvar("sv_soccar_gravity").getStringValue();
    this->plugin->cvarManager->registerCvar("speedrun_mutator_game_gravity", currentGameGravity, "Current game gravity")
            .addOnValueChanged([this](const std::string &oldValue, CVarWrapper cvar) {
                if (this->plugin->cvarManager->getCvar("sv_soccar_gravity").getFloatValue() != cvar.getFloatValue())
                {
                    this->plugin->cvarManager->getCvar("sv_soccar_gravity").setValue(cvar.getFloatValue());
                }
            });

    this->plugin->cvarManager->getCvar("sv_soccar_gravity")
            .addOnValueChanged([this](const std::string &oldValue, CVarWrapper cvar) {
                if (this->plugin->cvarManager->getCvar("speedrun_mutator_game_gravity").getFloatValue() != cvar.getFloatValue())
                {
                    this->plugin->cvarManager->getCvar("speedrun_mutator_game_gravity").setValue(cvar.getFloatValue());
                }
            });
}

void MutatorsToolkit::createGameSpeedCVar()
{
    std::string currentGameSpeed = this->plugin->cvarManager->getCvar("sv_soccar_gamespeed").getStringValue();
    this->plugin->cvarManager->registerCvar("speedrun_mutator_game_speed", currentGameSpeed, "Current game speed")
            .addOnValueChanged([this](const std::string &oldValue, CVarWrapper cvar) {
                if (this->plugin->cvarManager->getCvar("sv_soccar_gamespeed").getFloatValue() != cvar.getFloatValue())
                {
                    this->plugin->cvarManager->getCvar("sv_soccar_gamespeed").setValue(cvar.getFloatValue());
                }
            });

    this->plugin->cvarManager->getCvar("sv_soccar_gamespeed")
            .addOnValueChanged([this](const std::string &oldValue, CVarWrapper cvar) {
                if (this->plugin->cvarManager->getCvar("speedrun_mutator_game_speed").getFloatValue() != cvar.getFloatValue())
                {
                    this->plugin->cvarManager->getCvar("speedrun_mutator_game_speed").setValue(cvar.getFloatValue());
                }
            });
}

void MutatorsToolkit::createBoostMutatorCVar()
{
    this->plugin->cvarManager->registerCvar("speedrun_mutator_car_boost", "0", "Boost mutator").addOnValueChanged(
            [this](const std::string &oldValue, CVarWrapper cvar) {
                int boostMutator = cvar.getIntValue();
                if (boostMutator == BoostMutatorComponent::BoostMutator::Unlimited)
                {
                    this->boostMutatorComponent.setBoostMutator(BoostMutatorComponent::BoostMutator::Unlimited);
                }
                else if (boostMutator == BoostMutatorComponent::BoostMutator::Zero)
                {
                    this->boostMutatorComponent.setBoostMutator(BoostMutatorComponent::BoostMutator::Zero);
                }
                else
                {
                    this->boostMutatorComponent.setBoostMutator(BoostMutatorComponent::BoostMutator::None);
                }
            });
}

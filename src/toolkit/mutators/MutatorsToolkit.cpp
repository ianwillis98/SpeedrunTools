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
    this->createAutoAirRollMutator();
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

    ImGui::Text("Mutators Toolkit allows you to set custom mutators for fun and for custom run categories.");
    ImGui::Text("The following tools will only work in freeplay and workshop maps.");

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    this->boostMutatorComponent.render();

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    this->autoAirRollComponent.render();

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

void MutatorsToolkit::createAutoAirRollMutator()
{
    this->plugin->cvarManager->registerCvar("speedrun_mutator_car_autoairroll", "0", "Boost mutator").addOnValueChanged(
            [this](const std::string &oldValue, CVarWrapper cvar) {
                int autoAirRollMutator = cvar.getIntValue();
                if (autoAirRollMutator == AutoAirRollComponent::AirRollMutator::DisableAirRoll)
                {
                    this->autoAirRollComponent.setAirRollMutator(AutoAirRollComponent::AirRollMutator::DisableAirRoll);
                }
                else if (autoAirRollMutator == AutoAirRollComponent::AirRollMutator::AutoAirRollLeft)
                {
                    this->autoAirRollComponent.setAirRollMutator(AutoAirRollComponent::AirRollMutator::AutoAirRollLeft);
                }
                else if (autoAirRollMutator == AutoAirRollComponent::AirRollMutator::AutoAirRollRight)
                {
                    this->autoAirRollComponent.setAirRollMutator(AutoAirRollComponent::AirRollMutator::AutoAirRollRight);
                }
                else
                {
                    this->autoAirRollComponent.setAirRollMutator(AutoAirRollComponent::AirRollMutator::None);
                }
            });
}

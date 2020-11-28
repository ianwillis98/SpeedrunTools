#include "MutatorsComponent.h"

MutatorsComponent::MutatorsComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponent(plugin), boostMutator(BoostMutator::None), airRollMutator(AirRollMutator::None)
{

}

std::string MutatorsComponent::title()
{
    return "Mutators";
}

void MutatorsComponent::onLoad()
{
    this->createBoostMutatorCVar();
    this->createAirRollMutatorCVar();
    this->createGameGravityMutatorCVar();
    this->createGameSpeedMutatorCVar();
}

void MutatorsComponent::render()
{
    ImGui::Spacing();
    ImGui::Text("Set custom mutators that can be used for alternate speedrun categories.");
    ImGui::Text("Note that speedrun.com doesn't have categories for mutated runs.");
    ImGui::Spacing();

    ImGui::Separator();

    this->renderBoostMutator();
    ImGui::Separator();
    this->renderAirRollMutator();
    ImGui::Separator();
    this->renderGameGravityMutator();
    ImGui::Separator();
    this->renderGameSpeedMutator();
}

void MutatorsComponent::onEvent(std::string eventName, bool post, void *params)
{
    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && !post)
    {
        if (!this->plugin->gameWrapper->IsInFreeplay()) return;

        switch (this->boostMutator)
        {
            case BoostMutator::None:
                // do nothing
                break;
            case BoostMutator::ZeroBoost:
                this->setBoostAmount(0.0f);
                break;
            case BoostMutator::UnlimitedBoost:
                this->setBoostAmount(100.0f);
                break;
        }
    }
    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && !post && params != nullptr)
    {
        if (!this->plugin->gameWrapper->IsInFreeplay()) return;

        auto *controllerInput = (ControllerInput *) params;
        switch (this->airRollMutator)
        {
            case AirRollMutator::None:
                // do nothing
                break;
            case AirRollMutator::DisableAirRoll:
                controllerInput->Roll = 0.0f;
                break;
            case AirRollMutator::AutoAirRollLeft:
                controllerInput->Roll = -1.0f;
                break;
            case AirRollMutator::AutoAirRollRight:
                controllerInput->Roll = 1.0f;
                break;
        }
    }
}

void MutatorsComponent::setBoostAmount(float amount)
{
    CarWrapper car = this->plugin->gameWrapper->GetLocalCar();
    if (car.IsNull()) return;

    BoostWrapper boost = car.GetBoostComponent();
    if (boost.IsNull()) return;

    boost.SetBoostAmount(amount);
}

void MutatorsComponent::createBoostMutatorCVar()
{
    this->plugin->cvarManager->registerCvar("speedrun_mutators_car_boost", "0", "Boost mutator").addOnValueChanged(
            [this](const std::string &oldValue, CVarWrapper boostMutatorCVar) {
                switch (boostMutatorCVar.getIntValue())
                {
                    case static_cast<int>(BoostMutator::None):
                        this->boostMutator = BoostMutator::None;
                        break;
                    case static_cast<int>(BoostMutator::ZeroBoost):
                        this->boostMutator = BoostMutator::ZeroBoost;
                        break;
                    case static_cast<int>(BoostMutator::UnlimitedBoost):
                        this->boostMutator = BoostMutator::UnlimitedBoost;
                        break;
                    default:
                        this->boostMutator = BoostMutator::None;
                }
            });
}

void MutatorsComponent::createAirRollMutatorCVar()
{
    this->plugin->cvarManager->registerCvar("speedrun_mutators_car_airroll", "0", "Air roll mutator").addOnValueChanged(
            [this](const std::string &oldValue, CVarWrapper autoAirRollCVar) {
                switch (autoAirRollCVar.getIntValue())
                {
                    case static_cast<int>(AirRollMutator::None):
                        this->airRollMutator = AirRollMutator::None;
                        break;
                    case static_cast<int>(AirRollMutator::DisableAirRoll):
                        this->airRollMutator = AirRollMutator::DisableAirRoll;
                        break;
                    case static_cast<int>(AirRollMutator::AutoAirRollLeft):
                        this->airRollMutator = AirRollMutator::AutoAirRollLeft;
                        break;
                    case static_cast<int>(AirRollMutator::AutoAirRollRight):
                        this->airRollMutator = AirRollMutator::AutoAirRollRight;
                        break;
                    default:
                        this->airRollMutator = AirRollMutator::None;
                }
            });
}

void MutatorsComponent::createGameGravityMutatorCVar()
{
    std::string currentGameGravity = this->plugin->cvarManager->getCvar("sv_soccar_gravity").getStringValue();
    this->plugin->cvarManager->registerCvar("speedrun_mutators_game_gravity", currentGameGravity, "Current game gravity")
            .addOnValueChanged([this](const std::string &oldValue, CVarWrapper gameGravityMutatorCVar) {
                if (this->plugin->cvarManager->getCvar("sv_soccar_gravity").getFloatValue() != gameGravityMutatorCVar.getFloatValue())
                {
                    this->plugin->cvarManager->getCvar("sv_soccar_gravity").setValue(gameGravityMutatorCVar.getFloatValue());
                }
            });
    this->plugin->cvarManager->getCvar("sv_soccar_gravity")
            .addOnValueChanged([this](const std::string &oldValue, CVarWrapper svSoccarGravityCVar) {
                if (this->plugin->cvarManager->getCvar("speedrun_mutators_game_gravity").getFloatValue() != svSoccarGravityCVar.getFloatValue())
                {
                    this->plugin->cvarManager->getCvar("speedrun_mutators_game_gravity").setValue(svSoccarGravityCVar.getFloatValue());
                }
            });
}

void MutatorsComponent::createGameSpeedMutatorCVar()
{
    std::string currentGameSpeed = this->plugin->cvarManager->getCvar("sv_soccar_gamespeed").getStringValue();
    this->plugin->cvarManager->registerCvar("speedrun_mutators_game_speed", currentGameSpeed, "Current game speed")
            .addOnValueChanged([this](const std::string &oldValue, CVarWrapper gameSpeedMutatorCVar) {
                if (this->plugin->cvarManager->getCvar("sv_soccar_gamespeed").getFloatValue() != gameSpeedMutatorCVar.getFloatValue())
                {
                    this->plugin->cvarManager->getCvar("sv_soccar_gamespeed").setValue(gameSpeedMutatorCVar.getFloatValue());
                }
            });
    this->plugin->cvarManager->getCvar("sv_soccar_gamespeed")
            .addOnValueChanged([this](const std::string &oldValue, CVarWrapper svSoccarGamespeedCVar) {
                if (this->plugin->cvarManager->getCvar("speedrun_mutators_game_speed").getFloatValue() != svSoccarGamespeedCVar.getFloatValue())
                {
                    this->plugin->cvarManager->getCvar("speedrun_mutatos_game_speed").setValue(svSoccarGamespeedCVar.getFloatValue());
                }
            });
}

void MutatorsComponent::renderBoostMutator()
{
    ImGui::PushID("boost");
    ImGui::Text("Boost Mutator");
    ImGui::Spacing();
    if (ImGui::RadioButton("Off", this->boostMutator == BoostMutator::None))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->plugin->cvarManager->getCvar("speedrun_mutators_car_boost").setValue(static_cast<int>(BoostMutator::None));
        });
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Zero Boost", this->boostMutator == BoostMutator::ZeroBoost))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->plugin->cvarManager->getCvar("speedrun_mutators_car_boost").setValue(static_cast<int>(BoostMutator::ZeroBoost));
        });
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Unlimited Boost", this->boostMutator == BoostMutator::UnlimitedBoost))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->plugin->cvarManager->getCvar("speedrun_mutators_car_boost").setValue(static_cast<int>(BoostMutator::UnlimitedBoost));
        });
    }
    ImGui::PopID();
}

void MutatorsComponent::renderAirRollMutator()
{
    ImGui::PushID("airroll");
    ImGui::Text("Air Roll Mutator");
    ImGui::Spacing();
    if (ImGui::RadioButton("Off", this->airRollMutator == AirRollMutator::None))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->plugin->cvarManager->getCvar("speedrun_mutators_car_airroll").setValue(static_cast<int>(AirRollMutator::None));
        });
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Disable Air Roll", this->airRollMutator == AirRollMutator::DisableAirRoll))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->plugin->cvarManager->getCvar("speedrun_mutators_car_airroll").setValue(static_cast<int>(AirRollMutator::DisableAirRoll));
        });
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Auto Air Roll Left", this->airRollMutator == AirRollMutator::AutoAirRollLeft))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->plugin->cvarManager->getCvar("speedrun_mutators_car_airroll").setValue(static_cast<int>(AirRollMutator::AutoAirRollLeft));
        });
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Auto Air Roll Right", this->airRollMutator == AirRollMutator::AutoAirRollRight))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->plugin->cvarManager->getCvar("speedrun_mutators_car_airroll").setValue(static_cast<int>(AirRollMutator::AutoAirRollRight));
        });
    }
    ImGui::PopID();
}

void MutatorsComponent::renderGameGravityMutator()
{
    ImGui::PushID("gravity");
    ImGui::Text("Custom Game Gravity");
    ImGui::Spacing();
    float gameGravity = this->plugin->cvarManager->getCvar("speedrun_mutators_game_gravity").getFloatValue();
    if (ImGui::SliderFloat("Game Gravity", &gameGravity, -2000.0f, 2000.0f, "%.3f"))
    {
        this->plugin->gameWrapper->Execute([this, gameGravity](GameWrapper *gw) {
            this->plugin->cvarManager->getCvar("speedrun_mutators_game_gravity").setValue(gameGravity);
        });
    }
    if (ImGui::Button("Default"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->plugin->cvarManager->getCvar("speedrun_mutators_game_gravity").setValue(-650.0f);
        });
    }
    ImGui::SameLine();
    if (ImGui::Button("Zero"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->plugin->cvarManager->getCvar("speedrun_mutators_game_gravity").setValue(-0.001f);
        });
    }
    ImGui::SameLine();
    if (ImGui::Button("Inverse"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->plugin->cvarManager->getCvar("speedrun_mutators_game_gravity").setValue(650.0f);
        });
    }
    ImGui::PopID();
}

void MutatorsComponent::renderGameSpeedMutator()
{
    ImGui::PushID("speed");
    ImGui::Text("Custom Game Speed");
    ImGui::Spacing();
    float gameSpeed = this->plugin->cvarManager->getCvar("speedrun_mutators_game_speed").getFloatValue();
    if (ImGui::SliderFloat("Game Speed", &gameSpeed, 0.05f, 5.0f, "%.3f"))
    {
        this->plugin->gameWrapper->Execute([this, gameSpeed](GameWrapper *gw) {
            this->plugin->cvarManager->getCvar("speedrun_mutators_game_speed").setValue(gameSpeed);
        });
    }
    if (ImGui::Button("Default"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->plugin->cvarManager->getCvar("speedrun_mutators_game_speed").setValue(1.0f);
        });
    }
    ImGui::SameLine();
    if (ImGui::Button("Slow-mo"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->plugin->cvarManager->getCvar("speedrun_mutators_game_speed").setValue(0.67f);
        });
    }
    ImGui::SameLine();
    if (ImGui::Button("Fast-mo"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->plugin->cvarManager->getCvar("speedrun_mutators_game_speed").setValue(1.5f);
        });
    }
    ImGui::PopID();
}

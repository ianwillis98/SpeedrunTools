#include "GeneralToolsComponent.h"

const std::string GeneralToolsComponent::BoostMutatorCVarName = "speedrun_mutator_car_boost";
const std::string GeneralToolsComponent::AirRollMutatorCVarName = "speedrun_mutator_car_airroll";
const std::string GeneralToolsComponent::GameGravityMutatorCVarName = "speedrun_mutator_game_gravity";
const std::string GeneralToolsComponent::GameSpeedMutatorCVarName = "speedrun_mutator_game_speed";

GeneralToolsComponent::GeneralToolsComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponentBase(plugin),
          currentGameState(),
          boostMutator(BoostMutator::None),
          airRollMutator(AirRollMutator::None)
{
    this->createBoostMutatorCVar();
    this->createAirRollMutatorCVar();
    this->createGameGravityMutatorCVar();
    this->createGameSpeedMutatorCVar();
}

void GeneralToolsComponent::render()
{
    ImGui::PushID(this);

    ImGui::Text("General Tools");
    ImGuiExtensions::BigSeparator();
    this->renderCurrentGameState();
    ImGuiExtensions::BigSeparator();
    this->renderGameGravityMutator();
    ImGuiExtensions::BigSeparator();
    this->renderGameSpeedMutator();
    ImGuiExtensions::BigSeparator();
    this->renderBoostMutator();
    ImGuiExtensions::BigSeparator();
    this->renderAirRollMutator();

    ImGui::PopID();
}

void GeneralToolsComponent::onEvent(const std::string &eventName, bool post, void *params)
{
    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && !post)
    {
        if (!this->plugin->gameWrapper->IsInFreeplay()) return;

        ServerWrapper serverWrapper = this->plugin->gameWrapper->GetGameEventAsServer();
        if (serverWrapper.IsNull()) return;

        this->currentGameState = GameState(serverWrapper);
    }
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
            case AirRollMutator::ForceAirRollLeft:
                controllerInput->Roll = -1.0f;
                break;
            case AirRollMutator::ForceAirRollRight:
                controllerInput->Roll = 1.0f;
                break;
        }
    }
}

void GeneralToolsComponent::setBoostAmount(float amount)
{
    CarWrapper car = this->plugin->gameWrapper->GetLocalCar();
    if (car.IsNull()) return;

    BoostWrapper boost = car.GetBoostComponent();
    if (boost.IsNull()) return;

    boost.SetBoostAmount(amount);
}

void GeneralToolsComponent::createBoostMutatorCVar()
{
    this->plugin->cvarManager->registerCvar(BoostMutatorCVarName, "0").addOnValueChanged(
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

void GeneralToolsComponent::createAirRollMutatorCVar()
{
    this->plugin->cvarManager->registerCvar(AirRollMutatorCVarName, "0").addOnValueChanged(
            [this](const std::string &oldValue, CVarWrapper autoAirRollCVar) {
                switch (autoAirRollCVar.getIntValue())
                {
                    case static_cast<int>(AirRollMutator::None):
                        this->airRollMutator = AirRollMutator::None;
                        break;
                    case static_cast<int>(AirRollMutator::DisableAirRoll):
                        this->airRollMutator = AirRollMutator::DisableAirRoll;
                        break;
                    case static_cast<int>(AirRollMutator::ForceAirRollLeft):
                        this->airRollMutator = AirRollMutator::ForceAirRollLeft;
                        break;
                    case static_cast<int>(AirRollMutator::ForceAirRollRight):
                        this->airRollMutator = AirRollMutator::ForceAirRollRight;
                        break;
                    default:
                        this->airRollMutator = AirRollMutator::None;
                }
            });
}

void GeneralToolsComponent::createGameGravityMutatorCVar()
{
    CVarFunctions::createCVarReflection(this->plugin, GameGravityMutatorCVarName, "sv_soccar_gravity");
}

void GeneralToolsComponent::createGameSpeedMutatorCVar()
{
    CVarFunctions::createCVarReflection(this->plugin, GameSpeedMutatorCVarName, "sv_soccar_gamespeed");
}

void GeneralToolsComponent::renderCurrentGameState()
{
    if (this->currentGameState.render())
    {
        GameState newGameState = this->currentGameState;
        this->plugin->gameWrapper->Execute([this, newGameState](GameWrapper *gw) {
            ServerWrapper server = this->plugin->gameWrapper->GetGameEventAsServer();
            if (server.IsNull()) return;

            newGameState.applyTo(server);
        });
    }
}

void GeneralToolsComponent::renderBoostMutator()
{
    ImGui::PushID("boost");
    ImGui::Text("Boost Mutator");
    ImGui::Spacing();
    if (ImGui::RadioButton("Off", this->boostMutator == BoostMutator::None))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->plugin->cvarManager->getCvar(BoostMutatorCVarName).setValue(static_cast<int>(BoostMutator::None));
        });
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Zero Boost", this->boostMutator == BoostMutator::ZeroBoost))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->plugin->cvarManager->getCvar(BoostMutatorCVarName).setValue(static_cast<int>(BoostMutator::ZeroBoost));
        });
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Unlimited Boost", this->boostMutator == BoostMutator::UnlimitedBoost))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->plugin->cvarManager->getCvar(BoostMutatorCVarName).setValue(static_cast<int>(BoostMutator::UnlimitedBoost));
        });
    }
    ImGui::PopID();
}

void GeneralToolsComponent::renderAirRollMutator()
{
    ImGui::PushID("airroll");
    ImGui::Text("Air Roll Mutator");
    ImGui::Spacing();
    if (ImGui::RadioButton("Off", this->airRollMutator == AirRollMutator::None))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->plugin->cvarManager->getCvar(AirRollMutatorCVarName).setValue(static_cast<int>(AirRollMutator::None));
        });
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Disable Air Roll", this->airRollMutator == AirRollMutator::DisableAirRoll))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->plugin->cvarManager->getCvar(AirRollMutatorCVarName).setValue(static_cast<int>(AirRollMutator::DisableAirRoll));
        });
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Force Air Roll Left", this->airRollMutator == AirRollMutator::ForceAirRollLeft))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->plugin->cvarManager->getCvar(AirRollMutatorCVarName).setValue(static_cast<int>(AirRollMutator::ForceAirRollLeft));
        });
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Force Air Roll Right", this->airRollMutator == AirRollMutator::ForceAirRollRight))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->plugin->cvarManager->getCvar(AirRollMutatorCVarName).setValue(static_cast<int>(AirRollMutator::ForceAirRollRight));
        });
    }
    ImGui::PopID();
}

void GeneralToolsComponent::renderGameGravityMutator()
{
    ImGui::PushID(this);
    ImGui::Text("Game Gravity");
    ImGui::Spacing();
    float gameGravity = this->plugin->cvarManager->getCvar(GameGravityMutatorCVarName).getFloatValue();
    if (ImGui::SliderFloat("Game Gravity", &gameGravity, -2000.0f, 2000.0f, "%.3f"))
    {
        this->plugin->gameWrapper->Execute([this, gameGravity](GameWrapper *gw) {
            this->plugin->cvarManager->getCvar(GameGravityMutatorCVarName).setValue(gameGravity);
        });
    }
    if (ImGui::Button("Default"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->plugin->cvarManager->getCvar(GameGravityMutatorCVarName).setValue(-650.0f);
        });
    }
    ImGui::SameLine();
    if (ImGui::Button("Zero"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->plugin->cvarManager->getCvar(GameGravityMutatorCVarName).setValue(-0.001f);
        });
    }
    ImGui::SameLine();
    if (ImGui::Button("Inverse"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->plugin->cvarManager->getCvar(GameGravityMutatorCVarName).setValue(650.0f);
        });
    }
    ImGui::PopID();
}

void GeneralToolsComponent::renderGameSpeedMutator()
{
    ImGui::PushID("speed");
    ImGui::Text("Game Speed");
    ImGui::Spacing();
    float gameSpeed = this->plugin->cvarManager->getCvar(GameSpeedMutatorCVarName).getFloatValue();
    if (ImGui::SliderFloat("Game Speed", &gameSpeed, 0.05f, 5.0f, "%.3f"))
    {
        this->plugin->gameWrapper->Execute([this, gameSpeed](GameWrapper *gw) {
            this->plugin->cvarManager->getCvar(GameSpeedMutatorCVarName).setValue(gameSpeed);
        });
    }
    if (ImGui::Button("Default"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->plugin->cvarManager->getCvar(GameSpeedMutatorCVarName).setValue(1.0f);
        });
    }
    ImGui::SameLine();
    if (ImGui::Button("Slow-mo"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->plugin->cvarManager->getCvar(GameSpeedMutatorCVarName).setValue(0.67f);
        });
    }
    ImGui::SameLine();
    if (ImGui::Button("Fast-mo"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->plugin->cvarManager->getCvar(GameSpeedMutatorCVarName).setValue(1.5f);
        });
    }
    ImGui::PopID();
}

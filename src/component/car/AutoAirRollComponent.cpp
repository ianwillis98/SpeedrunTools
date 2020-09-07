#include "AutoAirRollComponent.h"
#include "../../services/MultiEventHooker.h"
#include "../../utils/LocalControllerInputFix.h"

AutoAirRollComponent::AutoAirRollComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponent(plugin), mutator(AirRollMutator::None)
{

}

void AutoAirRollComponent::onLoad()
{
    MultiEventHooker::getInstance(this->plugin).hookEventPost("Function TAGame.Car_TA.SetVehicleInput", [this](const std::string &eventName) {
        this->onPhysicsTick();
    });
}

void AutoAirRollComponent::onUnload()
{

}

void AutoAirRollComponent::render()
{
    ImGui::PushID(this);

    ImGui::Text("Air Roll Mutator");

    ImGui::Spacing();

    if (ImGui::RadioButton("No Mutator", this->mutator == AirRollMutator::None))
    {
        this->setAirRollMutator(AirRollMutator::None);
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Disable Air Roll", this->mutator == AirRollMutator::DisableAirRoll))
    {
        this->setAirRollMutator(AirRollMutator::DisableAirRoll);
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Auto Air Roll Left", this->mutator == AirRollMutator::AutoAirRollLeft))
    {
        this->setAirRollMutator(AirRollMutator::AutoAirRollLeft);
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Auto Air Roll Right", this->mutator == AirRollMutator::AutoAirRollRight))
    {
        this->setAirRollMutator(AirRollMutator::AutoAirRollRight);
    }

    ImGui::PopID();
}

void AutoAirRollComponent::onPhysicsTick()
{
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;

    switch (this->getAirRollMutator())
    {
        case AirRollMutator::None:
            // do nothing
            break;
        case AirRollMutator::DisableAirRoll:
            this->setAirRollAmount(0.0f);
            break;
        case AirRollMutator::AutoAirRollLeft:
            this->setAirRollAmount(-1.0f);
            break;
        case AirRollMutator::AutoAirRollRight:
            this->setAirRollAmount(1.0f);
            break;
    }
}

void AutoAirRollComponent::setAirRollAmount(float amount)
{
    CarWrapper car = this->plugin->gameWrapper->GetLocalCar();
    if (car.IsNull()) return;

    ControllerInput input = car.GetInput();
    input.Roll = amount;
    LocalControllerInputFix::fix(input);
    car.eventSetVehicleInput(input);
}

AutoAirRollComponent::AirRollMutator AutoAirRollComponent::getAirRollMutator()
{
    return this->mutator;
}

void AutoAirRollComponent::setAirRollMutator(AirRollMutator m)
{
    this->mutator = m;
}

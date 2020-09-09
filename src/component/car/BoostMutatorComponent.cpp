#include "BoostMutatorComponent.h"
#include "../../services/MultiEventHooker.h"

BoostMutatorComponent::BoostMutatorComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponent(plugin), mutator(BoostMutator::None)
{

}

void BoostMutatorComponent::onLoad()
{
    //"Function TAGame.Mutator_Freeplay_TA.Init"
    //"Function TAGame.GameEvent_Soccar_TA.Destroyed"
    MultiEventHooker::getInstance(this->plugin).hookEvent("Function TAGame.Car_TA.SetVehicleInput", [this](const std::string &eventName) {
        this->onPhysicsTick();
    });
}

void BoostMutatorComponent::onUnload()
{

}

void BoostMutatorComponent::render()
{
    ImGui::PushID(this);

    ImGui::Text("Boost Mutator");

    ImGui::Spacing();

    if (ImGui::RadioButton("Off", this->mutator == BoostMutator::None))
    {
        this->setBoostMutator(BoostMutator::None);
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Zero Boost", this->mutator == BoostMutator::Zero))
    {
        this->setBoostMutator(BoostMutator::Zero);
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Unlimited Boost", this->mutator == BoostMutator::Unlimited))
    {
        this->setBoostMutator(BoostMutator::Unlimited);
    }

    ImGui::PopID();
}

void BoostMutatorComponent::onPhysicsTick()
{
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;

    switch (this->getBoostMutator())
    {
        case BoostMutator::None:
            // do nothing
            break;
        case BoostMutator::Unlimited:
            this->setBoostAmount(100.0f);
            break;
        case BoostMutator::Zero:
            this->setBoostAmount(0.0f);
            break;
    }
}

void BoostMutatorComponent::setBoostAmount(float amount)
{
    CarWrapper car = this->plugin->gameWrapper->GetLocalCar();
    if (car.IsNull()) return;

    BoostWrapper boost = car.GetBoostComponent();
    if (boost.IsNull()) return;

    boost.SetBoostAmount(amount);
}

BoostMutatorComponent::BoostMutator BoostMutatorComponent::getBoostMutator()
{
    return this->mutator;
}

void BoostMutatorComponent::setBoostMutator(BoostMutator m)
{
    this->mutator = m;
}

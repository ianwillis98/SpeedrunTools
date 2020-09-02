#include "BoostMutatorComponent.h"
#include "../../services/MultiEventHooker.h"

BoostMutatorComponent::BoostMutatorComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponent(plugin), boostMutator(BoostMutator::None)
{

}

void BoostMutatorComponent::onLoad()
{
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

    ImGui::Text("Boost mutator");

    ImGui::Spacing();

    static int radioBoostMutator = BoostMutator::None;
    if (ImGui::RadioButton("None", &radioBoostMutator, BoostMutator::None))
    {
        this->setBoostMutator(BoostMutator::None);
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Unlimited Boost", &radioBoostMutator, BoostMutator::Unlimited))
    {
        this->setBoostMutator(BoostMutator::Unlimited);
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Zero Boost", &radioBoostMutator, BoostMutator::Zero))
    {
        this->setBoostMutator(BoostMutator::Zero);
    }

    ImGui::PopID();
}

void BoostMutatorComponent::onPhysicsTick()
{
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;

    switch (this->getBoostMutator())
    {
        case None:
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

BoostMutator BoostMutatorComponent::getBoostMutator()
{
    return this->boostMutator;
}

void BoostMutatorComponent::setBoostMutator(BoostMutator mutator)
{
    this->boostMutator = mutator;
}

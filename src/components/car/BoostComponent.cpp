#include "BoostComponent.h"
#include "../../services/MultiEventHooker.h"

BoostComponent::BoostComponent(BakkesMod::Plugin::BakkesModPlugin *plugin) : PluginComponent(plugin)
{

}

void BoostComponent::onLoad()
{
    CVarWrapper boost = this->plugin->cvarManager->registerCvar("speedrun_mutator_boost", "0", "Boost mutator");
    boost.addOnValueChanged([this](const std::string &oldValue, const CVarWrapper &cvar) {
        this->onBoostMutatorChanged();
    });


    MultiEventHooker::getInstance(this->plugin).hookEvent("Function TAGame.Car_TA.SetVehicleInput", [this](const std::string &eventName) {
        this->onPhysicsTick();
    });
}

void BoostComponent::onUnload()
{

}

void BoostComponent::render()
{
    ImGui::Text("Boost mutator");

    ImGui::Spacing();

    static int radioMutator = BoostMutator::None;
    if (ImGui::RadioButton("None", &radioMutator, BoostMutator::None))
    {
        this->setBoostMutator(BoostMutator::None);
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Unlimited Boost", &radioMutator, BoostMutator::Unlimited))
    {
        this->setBoostMutator(BoostMutator::Unlimited);
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Zero Boost", &radioMutator, BoostMutator::Zero))
    {
        this->setBoostMutator(BoostMutator::Zero);
    }
}

void BoostComponent::onPhysicsTick()
{
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;

    BoostMutator mutator = this->getBoostMutator();
    switch (mutator)
    {
        case None:
            // do nothing
            break;
        case BoostMutator::Unlimited:
            this->setBoostAmount(100.49f);
            break;
        case BoostMutator::Zero:
            this->setBoostAmount(0.0f);
            break;
    }
}

void BoostComponent::setBoostAmount(float amount)
{
    CarWrapper car = this->plugin->gameWrapper->GetLocalCar();
    if (car.IsNull()) return;

    BoostWrapper boost = car.GetBoostComponent();
    if (boost.IsNull()) return;

    boost.SetBoostAmount(amount);
}

BoostMutator BoostComponent::getBoostMutator()
{
    int mutator = this->plugin->cvarManager->getCvar("speedrun_mutator_boost").getIntValue();
    switch (mutator)
    {
        case BoostMutator::None:
            return BoostMutator::None;
        case BoostMutator::Unlimited:
            return BoostMutator::Unlimited;
        case BoostMutator::Zero:
            return BoostMutator::Zero;
        default:
            return BoostMutator::None;
    }
}

void BoostComponent::setBoostMutator(BoostMutator mutator)
{
    this->plugin->cvarManager->getCvar("speedrun_mutator_boost").setValue(mutator);
}

void BoostComponent::onBoostMutatorChanged()
{
    //this->plugin->cvarManager->log("boost mutator " + std::to_string(this->getBoostMutator()));
}

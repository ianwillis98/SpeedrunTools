#include "AirRollComponent.h"

AirRollComponent::AirRollComponent(BakkesMod::Plugin::BakkesModPlugin *plugin) : PluginComponent(plugin)
{

}

void AirRollComponent::onLoad()
{
    CVarWrapper componentEnabled = this->plugin->cvarManager->registerCvar("speedrun_mutator_airroll_enabled", "1", "Is custom gravity enabled");
    componentEnabled.addOnValueChanged([this](const std::string &oldValue, const CVarWrapper &cvar) {
        this->onComponentEnabledChanged();
    });
}

void AirRollComponent::onUnload()
{

}

void AirRollComponent::render()
{
    ImGui::Text("Auto air roll & No air roll mutators coming soon");
}

bool AirRollComponent::isComponentEnabled()
{
    return this->plugin->cvarManager->getCvar("speedrun_mutator_autoairroll_enabled").getBoolValue();
}

void AirRollComponent::setComponentEnabled(bool enabled)
{
    this->plugin->cvarManager->getCvar("speedrun_mutator_autoairroll_enabled").setValue(enabled);
}

void AirRollComponent::onComponentEnabledChanged()
{

}

#include "AutoAirRollComponent.h"

AutoAirRollComponent::AutoAirRollComponent(BakkesMod::Plugin::BakkesModPlugin *plugin) : PluginComponent(plugin)
{

}

void AutoAirRollComponent::onLoad()
{

}

void AutoAirRollComponent::onUnload()
{

}

void AutoAirRollComponent::render()
{
    ImGui::Text("Auto air roll coming soon");
}

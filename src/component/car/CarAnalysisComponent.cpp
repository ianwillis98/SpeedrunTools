#include "CarAnalysisComponent.h"
#include "../../services/MultiEventHooker.h"
#include "../../utils/ImGuiExtensions.h"

CarAnalysisComponent::CarAnalysisComponent(BakkesMod::Plugin::BakkesModPlugin *plugin) : PluginComponent(plugin)
{

}

void CarAnalysisComponent::onLoad()
{
    MultiEventHooker::getInstance(this->plugin).hookEvent("Function TAGame.Car_TA.SetVehicleInput", [this](const std::string &eventName) {
        this->onPhysicsTick();
    });
}

void CarAnalysisComponent::onUnload()
{

}

void CarAnalysisComponent::render()
{
    ImGui::Text("Current car state:");

    bool isInFreeplay = this->plugin->gameWrapper->IsInFreeplay();

    ImVec4 color = ImGui::GetStyle().Colors[isInFreeplay ? ImGuiCol_TextDisabled : ImGuiCol_Text];
    ImGui::TextColored(color, "(only works in freeplay and workshop maps)");

    ImGuiExtensions::PushDisabledStyleIf(!isInFreeplay);
    this->currentCarState.render();
    ImGuiExtensions::PopDisabledStyleIf(!isInFreeplay);
}

void CarAnalysisComponent::onPhysicsTick()
{
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;

    CarWrapper car = this->plugin->gameWrapper->GetLocalCar();
    if (car.IsNull()) return;

    this->currentCarState = CarState(car);
}

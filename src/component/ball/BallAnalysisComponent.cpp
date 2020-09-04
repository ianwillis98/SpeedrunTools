#include "BallAnalysisComponent.h"
#include "../../services/MultiEventHooker.h"
#include "../../utils/ImGuiExtensions.h"

BallAnalysisComponent::BallAnalysisComponent(BakkesMod::Plugin::BakkesModPlugin *plugin) : PluginComponent(plugin)
{

}

void BallAnalysisComponent::onLoad()
{
    MultiEventHooker::getInstance(this->plugin).hookEvent("Function TAGame.Car_TA.SetVehicleInput", [this](const std::string &eventName) {
        this->onPhysicsTick();
    });
}

void BallAnalysisComponent::onUnload()
{

}

void BallAnalysisComponent::render()
{
    ImGui::Text("Current ball state:");

    bool isInFreeplay = this->plugin->gameWrapper->IsInFreeplay();

    ImVec4 color = ImGui::GetStyle().Colors[isInFreeplay ? ImGuiCol_TextDisabled : ImGuiCol_Text];
    ImGui::TextColored(color, "(only works in freeplay and workshop maps)");

    ImGuiExtensions::PushDisabledStyleIf(!isInFreeplay);
    this->currentBallState.render();
    ImGuiExtensions::PopDisabledStyleIf(!isInFreeplay);
}

void BallAnalysisComponent::onPhysicsTick()
{
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;

    ServerWrapper server = this->plugin->gameWrapper->GetGameEventAsServer();
    if (server.IsNull()) return;

    BallWrapper ball = server.GetBall();
    if (ball.IsNull()) return;

    this->currentBallState = BallState(ball);
}

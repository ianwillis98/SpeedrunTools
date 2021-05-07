#include "RewindComponent.h"

RewindComponent::RewindComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponentBase(plugin),
          rewindBuffer(6.0f),
          previousSaveTime()
{
    this->plugin->cvarManager->registerCvar("speedrun_savestates_rewindlength", "6.0", "Rewind length")
            .addOnValueChanged([this](const std::string &oldValue, CVarWrapper rewindLengthCVar) {
                this->rewindBuffer.setRewindLength(rewindLengthCVar.getFloatValue());
            });
    this->plugin->cvarManager->registerCvar("speedrun_savestates_rewindsaveinterval", "0.1", "Rewind save interval");
    this->plugin->cvarManager->registerNotifier("speedrun_savestates_rewind", [this](const std::vector<std::string> &commands) {
        this->rewindGameState();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
}

void RewindComponent::render()
{
    ImGui::Text("Rewind Game State");
    ImGui::Spacing();
    bool isInFreeplay = this->plugin->gameWrapper->IsInFreeplay();
    ImGuiExtensions::PushDisabledStyleIf(!isInFreeplay);
    if (ImGui::Button("Rewind"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->rewindGameState();
        });
    }
    ImGuiExtensions::PopDisabledStyleIf(!isInFreeplay);
    ImGui::ProgressBar(this->rewindBuffer.progress(), ImVec2(0.f, 0.f), std::to_string(this->rewindBuffer.frontOffset()).c_str());
    ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
    ImGui::Text("Rewind buffer (in seconds)");
    float length = this->plugin->cvarManager->getCvar("speedrun_savestates_rewindlength").getFloatValue();
    if (ImGui::SliderFloat("Rewind length (in seconds)", &length, 1.0f, 30.0f, "%.3f"))
    {
        this->plugin->gameWrapper->Execute([this, length](GameWrapper *gw) {
            this->plugin->cvarManager->getCvar("speedrun_savestates_rewindlength").setValue(length);
        });
    }

    if (ImGui::Button("Default"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->plugin->cvarManager->getCvar("speedrun_savestates_rewindlength").setValue(6.0f);
        });
    }
    ImGui::SameLine();
    if (ImGui::Button("Short"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->plugin->cvarManager->getCvar("speedrun_savestates_rewindlength").setValue(3.0f);
        });
    }
    ImGui::SameLine();
    if (ImGui::Button("Long"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->plugin->cvarManager->getCvar("speedrun_savestates_rewindlength").setValue(12.0f);
        });
    }
}

void RewindComponent::onEvent(const std::string &eventName, bool post, void *params)
{
    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && !post)
    {
        if (!this->plugin->gameWrapper->IsInFreeplay()) return;

        ServerWrapper server = this->plugin->gameWrapper->GetGameEventAsServer();
        if (server.IsNull()) return;

        float currentTime = server.GetSecondsElapsed();

        float rewindSaveInterval = this->plugin->cvarManager->getCvar("speedrun_savestates_rewindsaveinterval").getFloatValue();
        if (this->rewindBuffer.empty() || currentTime > previousSaveTime + rewindSaveInterval)
        {
            GameState ss(server);
            this->rewindBuffer.push(ss);
            this->previousSaveTime = currentTime;
        }
    }
}

void RewindComponent::rewindGameState()
{
    if (this->rewindBuffer.empty()) return;
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;

    ServerWrapper server = this->plugin->gameWrapper->GetGameEventAsServer();
    if (server.IsNull()) return;

    this->rewindBuffer.removeAllButFront();
    this->rewindBuffer.front().applyTo(server);
}

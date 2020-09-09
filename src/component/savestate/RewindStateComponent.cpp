#include "RewindStateComponent.h"
#include "../../services/MultiEventHooker.h"
#include "../../utils/ImGuiExtensions.h"

RewindStateComponent::RewindStateComponent(BakkesMod::Plugin::BakkesModPlugin *plugin, float rewindLength, float rewindInterval)
        : PluginComponent(plugin), previousSaveTime(), rewindBuffer(rewindLength), rewindSaveInterval(rewindInterval)
{

}

void RewindStateComponent::onLoad()
{
    MultiEventHooker::getInstance(this->plugin).hookEvent("Function TAGame.Car_TA.SetVehicleInput", [this](const std::string &eventName) {
        this->onPhysicsTick();
    });
}

void RewindStateComponent::onUnload()
{

}

void RewindStateComponent::render()
{
    ImGui::PushID(this);

    ImGui::Text("Rewind Game State");

    ImGui::Spacing();

    bool isInFreeplay = this->plugin->gameWrapper->IsInFreeplay();
    ImGuiExtensions::PushDisabledStyleIf(!isInFreeplay);
    if (ImGui::Button("Rewind"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->rewind();
        });
    }
    ImGuiExtensions::PopDisabledStyleIf(!isInFreeplay);

    ImGui::ProgressBar(this->rewindBuffer.progress(), ImVec2(0.f, 0.f), std::to_string(this->rewindBuffer.frontOffset()).c_str());
    ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
    ImGui::Text("Rewind buffer (in seconds)");

    float length = this->getRewindLength();
    if (ImGui::SliderFloat("Rewind length (in seconds)", &length, 1.0f, 30.0f, "%.3f"))
    {
        this->plugin->gameWrapper->Execute([this, length](GameWrapper *gw) {
            this->setRewindLength(length);
        });
    }

    if (ImGui::Button("Default"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->setRewindLength(6.0f);
        });
    }
    ImGui::SameLine();
    if (ImGui::Button("Short"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->setRewindLength(3.0f);
        });
    }
    ImGui::SameLine();
    if (ImGui::Button("Long"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->setRewindLength(12.0f);
        });
    }

    ImGui::PopID();
}

void RewindStateComponent::onPhysicsTick()
{
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;

    ServerWrapper server = this->plugin->gameWrapper->GetGameEventAsServer();
    if (server.IsNull()) return;

    float currentTime = server.GetSecondsElapsed();

    if (this->rewindBuffer.empty() || currentTime > previousSaveTime + this->getRewindSaveInterval())
    {
        GameState ss(server);
        this->rewindBuffer.push(ss);
        this->previousSaveTime = currentTime;
    }
}

void RewindStateComponent::rewind()
{
    if (this->rewindBuffer.empty()) return;
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;

    ServerWrapper server = this->plugin->gameWrapper->GetGameEventAsServer();
    if (server.IsNull()) return;

    this->rewindBuffer.removeAllButFront();
    this->rewindBuffer.front().applyTo(server);
}

float RewindStateComponent::getRewindLength()
{
    return this->rewindBuffer.getRewindLength();
}

void RewindStateComponent::setRewindLength(float length)
{
    this->rewindBuffer.setRewindLength(length);
}

float RewindStateComponent::getRewindSaveInterval() const
{
    return this->rewindSaveInterval;
}

void RewindStateComponent::setRewindSaveInterval(float interval)
{
    this->rewindSaveInterval = interval;
}

#include "AutoSplitterComponent.h"

#include <utility>

AutoSplitterComponent::AutoSplitterComponent(BakkesMod::Plugin::BakkesModPlugin *plugin, std::string logPrefix)
        : PluginComponentBase(plugin),
          liveSplitClient(LiveSplitClient::getInstance()),
          logPrefix(std::move(logPrefix)),
          isEnabled(false),
          supportsAutoStart(true),
          isAutoStartEnabled(true),
          supportsAutoSplit(true),
          isAutoSplitEnabled(true),
          supportsAutoReset(true),
          isAutoResetEnabled(true)
{

}

void AutoSplitterComponent::render()
{
    if (!this->liveSplitClient.isConnected())
    {
        ImGui::Text("Connect to LiveSplit to use the auto splitter...");
        return;
    }

    ImGui::Checkbox("Enable Auto Splitter For This Map", &this->isEnabled);
    if (!this->isEnabled) return;

    ImGui::Spacing();

    ImGui::Text("Settings");

    ImGui::Spacing();

    if (this->supportsAutoStart) ImGui::Checkbox("Auto Start", &this->isAutoStartEnabled);
    if (this->supportsAutoSplit) ImGui::Checkbox("Auto Split", &this->isAutoSplitEnabled);
    if (this->supportsAutoReset) ImGui::Checkbox("Auto Reset", &this->isAutoResetEnabled);

    ImGui::Spacing();

    std::string debug = this->getDebugText();
    ImGui::InputTextMultiline("Debug Output", (char *) debug.c_str(), debug.capacity() + 1, ImVec2(0, ImGui::GetTextLineHeight() * 8),
                              ImGuiInputTextFlags_ReadOnly);
}

void AutoSplitterComponent::onEvent(const std::string &eventName, bool post, void *params)
{
    if (!this->isEnabled) return;

    this->update(eventName, post, params);
}

std::string AutoSplitterComponent::getStartDescription()
{
    return std::string();
}

std::string AutoSplitterComponent::getSplitDescription()
{
    return std::string();
}

std::string AutoSplitterComponent::getResetDescription()
{
    return std::string();
}

std::string AutoSplitterComponent::getDebugText()
{
    return this->logPrefix + " (Debug)";
}

void AutoSplitterComponent::startTimer()
{
    if (!this->liveSplitClient.isConnected() || !this->isEnabled || !this->isAutoStartEnabled) return;

    this->liveSplitClient.start([this](const int &errorCode, const std::string &errorMessage) {
        std::string log = (errorCode == 0) ? "starttimer" :
                          "Error while sending message 'start' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->log(log);
    });
}

void AutoSplitterComponent::splitTimer()
{
    if (!this->liveSplitClient.isConnected() || !this->isEnabled || !this->isAutoSplitEnabled) return;

    this->liveSplitClient.split([this](const int &errorCode, const std::string &errorMessage) {
        std::string log = (errorCode == 0) ? "split" :
                          "Error while sending message 'split' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->log(log);
    });
}

void AutoSplitterComponent::resetTimer()
{
    if (!this->liveSplitClient.isConnected() || !this->isEnabled || !this->isAutoSplitEnabled) return;

    this->liveSplitClient.reset([this](const int &errorCode, const std::string &errorMessage) {
        std::string log = (errorCode == 0) ? "reset" :
                          "Error while sending message 'reset' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->log(log);
    });
}

void AutoSplitterComponent::log(const std::string &message)
{
    this->plugin->cvarManager->log(this->logPrefix + ": " + message);
}

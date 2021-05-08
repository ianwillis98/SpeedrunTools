#include "AutoSplitterComponent.h"

#include <utility>

AutoSplitterComponent::AutoSplitterComponent(BakkesMod::Plugin::BakkesModPlugin *plugin, std::string runName)
        : PluginComponentBase(plugin),
          liveSplitModel(LiveSplitModel::getInstance(plugin)),
          runName(std::move(runName)),
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
    if (!this->liveSplitModel.isConnected())
    {
        ImGui::Text("Connect to LiveSplit to use the Auto Splitter...");
        ImGui::Spacing();
        this->renderConnectView();
        return;
    }

    if (!this->isEnabled)
        if (ImGui::Button("Enable Auto Splitter For This Map")) this->isEnabled = true;

    if (this->isEnabled)
        if (ImGui::Button("Disable Auto Splitter For This Map")) this->isEnabled = false;

    if (!this->isEnabled) return;

    ImGui::Spacing();

    ImGui::Text("Settings");

    ImGui::Spacing();

    if (this->supportsAutoStart) ImGui::Checkbox("Auto Start", &this->isAutoStartEnabled);
    if (this->supportsAutoSplit) ImGui::Checkbox("Auto Split", &this->isAutoSplitEnabled);
    if (this->supportsAutoReset) ImGui::Checkbox("Auto Reset", &this->isAutoResetEnabled);

    ImGui::Spacing();

    std::string debug = this->getDebugTextPrefix() + this->getDebugText();
    ImGui::InputTextMultiline("Debug Output", (char *) debug.c_str(), debug.capacity() + 1, ImVec2(0, ImGui::GetTextLineHeight() * 8),
                              ImGuiInputTextFlags_ReadOnly);
}

void AutoSplitterComponent::renderConnectView()
{
    if (!this->liveSplitModel.isConnected())
    {
        ImVec2 connectButtonSize(100.0f, 30.0f);
        ImGuiExtensions::PushDisabledStyleIf(this->liveSplitModel.isConnecting());
        if (ImGui::Button(this->liveSplitModel.isConnecting() ? "Connecting..." : "Connect", connectButtonSize))
        {
            this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
                this->liveSplitModel.connect();
            });
        }
        ImGuiExtensions::PopDisabledStyleIf(this->liveSplitModel.isConnecting());
    }
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

std::string AutoSplitterComponent::getDebugTextPrefix()
{
    std::stringstream ss;
    ss << this->runName + " Auto Splitter (Debug)" << std::endl;
    ss << "isEnabled = " << this->isEnabled << std::endl;
    ss << "supportsAutoStart = " << this->supportsAutoStart << std::endl;
    ss << "-------------------------------------" << std::endl;
    return ss.str();
}

std::string AutoSplitterComponent::getDebugText()
{
    return this->runName + " (Debug)";
}

void AutoSplitterComponent::startTimer()
{
    if (!this->liveSplitModel.isConnected() || !this->isEnabled || !this->isAutoStartEnabled) return;

    this->liveSplitModel.start();
}

void AutoSplitterComponent::splitTimer()
{
    if (!this->liveSplitModel.isConnected() || !this->isEnabled || !this->isAutoSplitEnabled) return;

    this->liveSplitModel.split();
}

void AutoSplitterComponent::resetTimer()
{
    if (!this->liveSplitModel.isConnected() || !this->isEnabled || !this->isAutoSplitEnabled) return;

    this->liveSplitModel.reset();
}

void AutoSplitterComponent::log(const std::string &message)
{
    this->plugin->cvarManager->log(this->runName + " Auto Splitter: " + message);
}

#include "AutoSplitterComponent.h"

AutoSplitterComponent::AutoSplitterComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponentBase(plugin),
          liveSplitModel(LiveSplitModel::getInstance(plugin)),
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
    ImGui::PushID(this);

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

    ImGuiExtensions::PushDisabledStyleIf(!this->supportsAutoStart);
    ImGui::Checkbox("Auto Start", &this->isAutoStartEnabled);
    ImGuiExtensions::PopDisabledStyleIf(!this->supportsAutoStart);
    if (!this->getStartDescription().empty())
    {
        ImGui::SameLine();
        ImGuiExtensions::PushDisabledStyleIf(!this->isAutoStartEnabled);
        ImGui::BulletText("%s", this->getStartDescription().c_str());
        ImGuiExtensions::PopDisabledStyleIf(!this->isAutoStartEnabled);
    }
    ImGui::Spacing();

    ImGuiExtensions::PushDisabledStyleIf(!this->supportsAutoSplit);
    ImGui::Checkbox("Auto Split", &this->isAutoSplitEnabled);
    ImGuiExtensions::PopDisabledStyleIf(!this->supportsAutoSplit);
    if (!this->getSplitDescription().empty())
    {
        ImGui::SameLine();
        ImGuiExtensions::PushDisabledStyleIf(!this->isAutoSplitEnabled);
        ImGui::BulletText("%s", this->getSplitDescription().c_str());
        ImGuiExtensions::PopDisabledStyleIf(!this->isAutoSplitEnabled);
    }
    ImGui::Spacing();

    ImGuiExtensions::PushDisabledStyleIf(!this->supportsAutoReset);
    ImGui::Checkbox("Auto Reset", &this->isAutoResetEnabled);
    ImGuiExtensions::PopDisabledStyleIf(!this->supportsAutoReset);
    if (!this->getResetDescription().empty())
    {
        ImGui::SameLine();
        ImGuiExtensions::PushDisabledStyleIf(!this->isAutoResetEnabled);
        ImGui::BulletText("%s", this->getResetDescription().c_str());
        ImGuiExtensions::PopDisabledStyleIf(!this->isAutoResetEnabled);
    }
    ImGui::Spacing();

    std::string debug = this->getDebugTextPrefix() + this->getDebugText();
    ImGui::InputTextMultiline("Debug Output", (char *) debug.c_str(), debug.capacity() + 1, ImVec2(0, ImGui::GetTextLineHeight() * 8),
                              ImGuiInputTextFlags_ReadOnly);

    ImGui::PopID();
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

std::string AutoSplitterComponent::getDebugTextPrefix() const
{
    std::stringstream ss;
    ss << "Auto Splitter (Debug)" << std::endl;
    ss << "isEnabled = " << this->isEnabled << std::endl;
    ss << "supportsAutoStart = " << this->supportsAutoStart << std::endl;
    ss << "isAutoStartEnabled = " << this->isAutoStartEnabled << std::endl;
    ss << "supportsAutoSplit = " << this->supportsAutoSplit << std::endl;
    ss << "isAutoSplitEnabled = " << this->isAutoSplitEnabled << std::endl;
    ss << "supportsAutoReset = " << this->supportsAutoReset << std::endl;
    ss << "isAutoResetEnabled = " << this->isAutoResetEnabled << std::endl;
    ss << "-------------------------------------" << std::endl;
    return ss.str();
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
    return std::string();
}


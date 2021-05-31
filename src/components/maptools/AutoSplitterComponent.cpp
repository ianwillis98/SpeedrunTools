#include "AutoSplitterComponent.h"

AutoSplitterComponent::AutoSplitterComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponentBase(plugin),
          liveSplitModel(LiveSplitModel::getInstance(plugin)),
          kismetModel(KismetModel::getInstance(plugin)),
          isEnabled(false),
          isAutoStartEnabled(true),
          isAutoSplitEnabled(true),
          isAutoResetEnabled(true),
          segment(0)
{

}

void AutoSplitterComponent::onEvent(const std::string &eventName, bool post, void *params)
{
    if (this->isEnabled)
    {
        this->update(eventName, post, params);
    }
}

void AutoSplitterComponent::render()
{
    if (this->liveSplitModel.isConnected())
    {
        if (this->isEnabled)
        {
            if (ImGui::Button("Disable Auto Splitter For This Map"))
                this->isEnabled = false;

            ImGuiExtensions::BigSpacing();

            ImGui::Checkbox("Auto Start", &this->isAutoStartEnabled);
            if (!this->getStartDescription().empty())
            {
                ImGuiExtensions::PushDisabledStyleIf(!this->isAutoStartEnabled);
                ImGui::Text("%s", this->getStartDescription().c_str());
                ImGuiExtensions::PopDisabledStyleIf(!this->isAutoStartEnabled);
            }
            ImGui::Spacing();

            ImGui::Checkbox("Auto Split", &this->isAutoSplitEnabled);
            if (!this->getSplitDescription().empty())
            {
                ImGuiExtensions::PushDisabledStyleIf(!this->isAutoSplitEnabled);
                ImGui::Text("%s", this->getSplitDescription().c_str());
                ImGuiExtensions::PopDisabledStyleIf(!this->isAutoSplitEnabled);
            }
            ImGui::Spacing();

            ImGui::Checkbox("Auto Reset", &this->isAutoResetEnabled);
            if (!this->getResetDescription().empty())
            {
                ImGuiExtensions::PushDisabledStyleIf(!this->isAutoResetEnabled);
                ImGui::Text("%s", this->getResetDescription().c_str());
                ImGuiExtensions::PopDisabledStyleIf(!this->isAutoResetEnabled);
            }
            ImGuiExtensions::BigSpacing();

            std::string debug = this->getDebugTextPrefix() + this->getDebugText();
            ImGui::InputTextMultiline("Debug Output", (char *) debug.c_str(), debug.capacity() + 1, ImVec2(0, ImGui::GetTextLineHeight() * 8),
                                      ImGuiInputTextFlags_ReadOnly);
        }
        else
        {
            if (ImGui::Button("Enable Auto Splitter For This Map"))
            {
                this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
                    this->onEnable();
                    this->isEnabled = true;
                });
            }
        }
    }
    else
    {
        this->renderConnectView();
    }
}

void AutoSplitterComponent::renderConnectView()
{
    if (!this->liveSplitModel.isConnected())
    {
        ImGui::Text("Connect to LiveSplit to use the Auto Splitter...");
        ImGui::Spacing();

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

void AutoSplitterComponent::onMapReset()
{
    this->reset();
}

void AutoSplitterComponent::onEnable()
{

}

void AutoSplitterComponent::start()
{
    this->segment = 1;
    if (this->liveSplitModel.isConnected() && this->isEnabled && this->isAutoStartEnabled) this->liveSplitModel.start();
}

void AutoSplitterComponent::split()
{
    this->segment++;
    if (this->liveSplitModel.isConnected() && this->isEnabled && this->isAutoSplitEnabled) this->liveSplitModel.split();
}

void AutoSplitterComponent::reset()
{
    this->segment = 0;
    if (this->liveSplitModel.isConnected() && this->isEnabled && this->isAutoResetEnabled) this->liveSplitModel.reset();
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

std::string AutoSplitterComponent::getDebugTextPrefix() const
{
    std::stringstream ss;
    ss << "Auto Splitter (Debug)" << std::endl;
    ss << "isEnabled = " << this->isEnabled << std::endl;
    ss << "isAutoStartEnabled = " << this->isAutoStartEnabled << std::endl;
    ss << "isAutoSplitEnabled = " << this->isAutoSplitEnabled << std::endl;
    ss << "isAutoResetEnabled = " << this->isAutoResetEnabled << std::endl;
    ss << "segment = " << this->segment << std::endl;
    ss << "-------------------------------------" << std::endl;
    return ss.str();
}

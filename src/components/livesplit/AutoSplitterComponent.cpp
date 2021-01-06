#include "AutoSplitterComponent.h"
#include "autosplitters/NullAutoSplitter.h"
#include "AutoSplitterFactory.h"

AutoSplitterComponent::AutoSplitterComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponentBase(plugin),
          liveSplitClient(LiveSplitClient::getInstance()),
          autoSplitter(std::make_unique<NullAutoSplitter>()),
          isAutoStartEnabled(true),
          isAutoSplitEnabled(true),
          isAutoResetEnabled(true)
{

}

void AutoSplitterComponent::onLoad()
{

}

void AutoSplitterComponent::render()
{
    ImGui::Text("Auto Splitter:");
    ImGui::Spacing();

    if (!this->liveSplitClient.isConnected())
    {
        ImGui::Text("Waiting for a connection to the LiveSplit Server...");
        return;
    }

    static int ci = 0;
    if (ImGui::Combo("Run/Category", &ci, AutoSplitterRunTemp::runNames, AutoSplitterRunTemp::runs.size()))
    {
        this->autoSplitter = AutoSplitterFactory::getInstance(this->plugin)
                .getAutoSplitterForRun(AutoSplitterRunTemp::runNames[ci]);
    }
    ImGui::Spacing();

    ImGuiExtensions::PushDisabledStyleIf(!this->autoSplitter->supportsAutoStart());
    ImGui::Checkbox("Auto Start Enabled", &this->isAutoStartEnabled);
    ImGuiExtensions::PopDisabledStyleIf(!this->autoSplitter->supportsAutoStart());

    ImGuiExtensions::PushDisabledStyleIf(!this->autoSplitter->supportsAutoSplit());
    ImGui::Checkbox("Auto Split Enabled", &this->isAutoSplitEnabled);
    ImGuiExtensions::PopDisabledStyleIf(!this->autoSplitter->supportsAutoSplit());

    ImGuiExtensions::PushDisabledStyleIf(!this->autoSplitter->supportsAutoReset());
    ImGui::Checkbox("Auto Reset Enabled", &this->isAutoResetEnabled);
    ImGuiExtensions::PopDisabledStyleIf(!this->autoSplitter->supportsAutoReset());

    ImGui::Spacing();

    std::string debug = this->autoSplitter->getDebug();
    ImGui::InputTextMultiline("Debug Output", (char *) debug.c_str(), debug.capacity() + 1, ImVec2(0, ImGui::GetTextLineHeight() * 8),
                              ImGuiInputTextFlags_ReadOnly);

    if (!this->autoSplitter->autoStartDescription().empty())
    {
        ImGui::Spacing();
        ImGui::Text("Auto Start Description: %s", this->autoSplitter->autoStartDescription().c_str());
    }
    if (!this->autoSplitter->autoSplitDescription().empty())
    {
        ImGui::Spacing();
        ImGui::Text("Auto Split Description: %s", this->autoSplitter->autoSplitDescription().c_str());
    }
    if (!this->autoSplitter->autoResetDescription().empty())
    {
        ImGui::Spacing();
        ImGui::Text("Auto Reset Description: %s", this->autoSplitter->autoResetDescription().c_str());
    }
}

void AutoSplitterComponent::onEvent(const std::string &eventName, bool post, void *params)
{
    if (!this->liveSplitClient.isConnected()) return;

    this->autoSplitter->onEvent(eventName, post, params);

    if (this->autoSplitter->update())
    {
        if (this->isAutoStartEnabled && this->autoSplitter->supportsAutoStart() && this->autoSplitter->shouldTimerStart()) this->start();
        if (this->isAutoSplitEnabled && this->autoSplitter->supportsAutoSplit() && this->autoSplitter->shouldTimerSplit()) this->split();
        if (this->isAutoResetEnabled && this->autoSplitter->supportsAutoReset() && this->autoSplitter->shouldTimerReset()) this->reset();
    }
}

void AutoSplitterComponent::start()
{
    this->liveSplitClient.start([this](const int &errorCode, const std::string &errorMessage) {
        this->feedbackMessage = (errorCode == 0) ? "'start' message was successfully sent." :
                                "Error while sending message 'start' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->log(this->feedbackMessage);
    });
}

void AutoSplitterComponent::split()
{
    this->liveSplitClient.split([this](const int &errorCode, const std::string &errorMessage) {
        this->feedbackMessage = (errorCode == 0) ? "'split' message was successfully sent." :
                                "Error while sending message 'split' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->log(this->feedbackMessage);
    });
}

void AutoSplitterComponent::reset()
{
    this->liveSplitClient.reset([this](const int &errorCode, const std::string &errorMessage) {
        this->feedbackMessage = (errorCode == 0) ? "'reset' message was successfully sent." :
                                "Error while sending message 'reset' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->log(this->feedbackMessage);
    });
}

void AutoSplitterComponent::log(const std::string &message)
{
    this->plugin->cvarManager->log("Auto Splitter: " + message);
    this->plugin->gameWrapper->Execute([this, message](GameWrapper *gw) {
        this->plugin->gameWrapper->LogToChatbox("Auto Splitter: " + message, "SPEEDRUNTOOLS");
    });
}

#include "TutorialBasicAutoSplitterComponent.h"

TutorialBasicAutoSplitterComponent::TutorialBasicAutoSplitterComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponentBase(plugin),
          liveSplitClient(LiveSplitClient::getInstance()),
          isEnabled(false),
          isAutoStartEnabled(true),
          isAutoSplitEnabled(true),
          isAutoResetEnabled(true),
          isInTutorial(false),
          segment(0)
{

}

void TutorialBasicAutoSplitterComponent::render()
{
    if (!this->liveSplitClient.isConnected())
    {
        ImGui::Text("Connect to LiveSplit to use the auto splitter...");
        return;
    }

    ImGui::Checkbox("Auto Splitter Enabled", &this->isEnabled);

    bool isAutoSplitterDisabled = !this->isEnabled;
    ImGuiExtensions::PushDisabledStyleIf(isAutoSplitterDisabled);
    ImGui::Spacing();

    ImGui::Checkbox("Auto Start", &this->isAutoStartEnabled);
    ImGui::Checkbox("Auto Split", &this->isAutoSplitEnabled);
    ImGui::Checkbox("Auto Reset", &this->isAutoResetEnabled);

    ImGui::Spacing();

    std::string debug = this->getDebugText();
    ImGui::InputTextMultiline("Debug Output", (char *) debug.c_str(), debug.capacity() + 1, ImVec2(0, ImGui::GetTextLineHeight() * 8),
                              ImGuiInputTextFlags_ReadOnly);

    ImGuiExtensions::PopDisabledStyleIf(isAutoSplitterDisabled);
}

void TutorialBasicAutoSplitterComponent::onEvent(const std::string &eventName, bool post, void *params)
{
    if (!this->isEnabled) return;

    if (eventName == "Function TAGame.GameInfo_Tutorial_TA.PostBeginPlay" && post)
    {
        this->isInTutorial = true;
    }
    if (eventName == "Function TAGame.GameEvent_Tutorial_TA.Destroyed" && post)
    {
        this->isInTutorial = false;

        if (segment > 0)
        {
            this->segment = 0;
            this->reset();
        }
    }
    if (eventName == "Function TAGame.GFxShell_TA.ShowModalObject" && post)
    {
        if (!this->isInTutorial) return;

        if (this->segment == 0)
        {
            CarWrapper cw = this->plugin->gameWrapper->GetLocalCar();
            if (cw.IsNull()) return;

            int yaw = cw.GetRotation().Yaw;
            if (yaw < 16000 || yaw > 16600) return;

            this->segment++;
            this->start();
        }
        else if (this->segment == 6)
        {
            CarWrapper cw = this->plugin->gameWrapper->GetLocalCar();
            if (cw.IsNull()) return;

            int yaw = cw.GetRotation().Yaw;
            if (yaw > 16000 && yaw < 16600) return;

            this->segment++;
            this->split();
        }
    }
    if (eventName == "Function GameEvent_Tutorial_Basic_TA.Active.HandleHitGoal" && post)
    {
        if (!this->isInTutorial) return;

        if (1 <= this->segment && this->segment <= 5)
        {
            this->segment++;
            this->split();
        }
    }
}

void TutorialBasicAutoSplitterComponent::start()
{
    if (!this->liveSplitClient.isConnected() || !this->isEnabled || !this->isAutoStartEnabled) return;

    this->liveSplitClient.start([this](const int &errorCode, const std::string &errorMessage) {
        std::string log = (errorCode == 0) ? "startTimer" :
                          "Error while sending message 'startTimer' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->log(log);
    });
}

void TutorialBasicAutoSplitterComponent::split()
{
    if (!this->liveSplitClient.isConnected() || !this->isEnabled || !this->isAutoSplitEnabled) return;

    this->liveSplitClient.split([this](const int &errorCode, const std::string &errorMessage) {
        std::string log = (errorCode == 0) ? "splitTimer" :
                          "Error while sending message 'splitTimer' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->log(log);
    });
}

void TutorialBasicAutoSplitterComponent::reset()
{
    if (!this->liveSplitClient.isConnected() || !this->isEnabled || !this->isAutoResetEnabled) return;

    this->liveSplitClient.reset([this](const int &errorCode, const std::string &errorMessage) {
        std::string log = (errorCode == 0) ? "resetTimer" :
                          "Error while sending message 'resetTimer' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->log(log);
    });
}

void TutorialBasicAutoSplitterComponent::log(const std::string &message)
{
    this->plugin->cvarManager->log("Tutorial Basic Auto Splitter: " + message);
}


std::string TutorialBasicAutoSplitterComponent::getDebugText() const
{
    std::stringstream ss;
    ss << "Tutorial Basic Auto Splitter (Debug)" << std::endl;
    ss << "isAutoSplitterEnabled = " << this->isEnabled << std::endl;
    ss << "isAutoStartEnabled = " << this->isAutoStartEnabled << std::endl;
    ss << "isAutoSplitEnabled = " << this->isAutoSplitEnabled << std::endl;
    ss << "isAutoResetEnabled = " << this->isAutoResetEnabled << std::endl;
    ss << "isInTutorial = " << this->isInTutorial << std::endl;
    ss << "segment = " << this->segment << std::endl;
    return ss.str();
}
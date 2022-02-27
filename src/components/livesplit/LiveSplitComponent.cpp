#include "LiveSplitComponent.h"

const std::string LiveSplitComponent::ConnectCVarName = "speedrun_livesplit_connect";
const std::string LiveSplitComponent::DisconnectCVarName = "speedrun_livesplit_disconnect";
const std::string LiveSplitComponent::StartOrSplitCVarName = "speedrun_livesplit_startorsplit";
const std::string LiveSplitComponent::StartCVarName = "speedrun_livesplit_start";
const std::string LiveSplitComponent::PauseCVarName = "speedrun_livesplit_pause";
const std::string LiveSplitComponent::ResumeCVarName = "speedrun_livesplit_resume";
const std::string LiveSplitComponent::ResetCVarName = "speedrun_livesplit_reset";
const std::string LiveSplitComponent::SplitCVarName = "speedrun_livesplit_split";
const std::string LiveSplitComponent::SkipSplitCVarName = "speedrun_livesplit_skipsplit";
const std::string LiveSplitComponent::UndoSplitCVarName = "speedrun_livesplit_undosplit";

LiveSplitComponent::LiveSplitComponent(NetcodePlugin *plugin)
        : PluginComponentBase(plugin),
          liveSplitModel(LiveSplitModel::getInstance(plugin))
{
    this->plugin->cvarManager->registerNotifier(ConnectCVarName, [this](const std::vector<std::string> &commands) {
        this->liveSplitModel.connect();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier(DisconnectCVarName, [this](const std::vector<std::string> &commands) {
        this->liveSplitModel.disconnect();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier(StartOrSplitCVarName, [this](const std::vector<std::string> &commands) {
        this->liveSplitModel.startOrSplit();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier(StartCVarName, [this](const std::vector<std::string> &commands) {
        this->liveSplitModel.start();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier(PauseCVarName, [this](const std::vector<std::string> &commands) {
        this->liveSplitModel.pause();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier(ResumeCVarName, [this](const std::vector<std::string> &commands) {
        this->liveSplitModel.resume();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier(ResetCVarName, [this](const std::vector<std::string> &commands) {
        this->liveSplitModel.reset();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier(SplitCVarName, [this](const std::vector<std::string> &commands) {
        this->liveSplitModel.split();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier(SkipSplitCVarName, [this](const std::vector<std::string> &commands) {
        this->liveSplitModel.skipSplit();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier(UndoSplitCVarName, [this](const std::vector<std::string> &commands) {
        this->liveSplitModel.undoSplit();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
}

void LiveSplitComponent::render()
{
    this->renderConnectionStatus();
    ImGuiExtensions::BigSpacing();
    this->renderRemoteControls();
}

void LiveSplitComponent::renderConnectionStatus()
{
    ImGui::BulletText("Connection Status: ");
    ImGui::SameLine();
    if (this->liveSplitModel.isConnected())
        ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Connected");
    else if (this->liveSplitModel.isConnecting())
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Connecting %c", "|/-\\"[(int) (ImGui::GetTime() / 0.05f) & 3]);
    else
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Not Connected");

    ImGui::BulletText("Status Message: %s", this->liveSplitModel.getStatusMessage().c_str());
}

void LiveSplitComponent::renderRemoteControls()
{
    ImGui::Text("Remote Controls:");
    ImGui::Spacing();

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
    if (this->liveSplitModel.isConnected())
    {
        ImVec2 bigButtonSize(100.0f, 30.0f);
        ImVec2 smallButtonSize(66.0f, 30.0f);
        if (ImGui::Button("Start", bigButtonSize))
        {
            this->plugin->gameWrapper->Execute([&](GameWrapper *gw) {
                this->liveSplitModel.start();
            });
        }
        ImGui::SameLine();
        if (ImGui::Button("Pause", smallButtonSize))
        {
            this->plugin->gameWrapper->Execute([&](GameWrapper *gw) {
                this->liveSplitModel.pause();
            });
        }
        ImGui::SameLine();
        if (ImGui::Button("Resume", smallButtonSize))
        {
            this->plugin->gameWrapper->Execute([&](GameWrapper *gw) {
                this->liveSplitModel.resume();
            });
        }
        ImGui::Spacing();

        if (ImGui::Button("Split", bigButtonSize))
        {
            this->plugin->gameWrapper->Execute([&](GameWrapper *gw) {
                this->liveSplitModel.split();
            });
        }
        ImGui::SameLine();
        if (ImGui::Button("Skip Split", smallButtonSize))
        {
            this->plugin->gameWrapper->Execute([&](GameWrapper *gw) {
                this->liveSplitModel.skipSplit();
            });
        }
        ImGui::SameLine();
        if (ImGui::Button("Undo Split", smallButtonSize))
        {
            this->plugin->gameWrapper->Execute([&](GameWrapper *gw) {
                this->liveSplitModel.undoSplit();
            });
        }
        ImGui::Spacing();

        if (ImGui::Button("Reset", bigButtonSize))
        {
            this->plugin->gameWrapper->Execute([&](GameWrapper *gw) {
                this->liveSplitModel.reset();
            });
        }
        ImGuiExtensions::BigSpacing();

        ImVec2 disconnectButtonSize(100.0f, 20.0f);
        if (ImGui::Button("Disconnect", disconnectButtonSize))
        {
            this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
                this->liveSplitModel.disconnect();
            });
        }
    }
}

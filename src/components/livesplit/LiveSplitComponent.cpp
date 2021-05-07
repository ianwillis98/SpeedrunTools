#include "LiveSplitComponent.h"

LiveSplitComponent::LiveSplitComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponentBase(plugin),
          liveSplitModel(LiveSplitModel::getInstance(plugin))
{
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_connect", [this](const std::vector<std::string> &commands) {
        this->liveSplitModel.connect();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_disconnect", [this](const std::vector<std::string> &commands) {
        this->liveSplitModel.disconnect();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_startorsplit", [this](const std::vector<std::string> &commands) {
        this->liveSplitModel.startOrSplit();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_start", [this](const std::vector<std::string> &commands) {
        this->liveSplitModel.start();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_pause", [this](const std::vector<std::string> &commands) {
        this->liveSplitModel.pause();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_resume", [this](const std::vector<std::string> &commands) {
        this->liveSplitModel.resume();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_reset", [this](const std::vector<std::string> &commands) {
        this->liveSplitModel.reset();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_split", [this](const std::vector<std::string> &commands) {
        this->liveSplitModel.split();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_skipsplit", [this](const std::vector<std::string> &commands) {
        this->liveSplitModel.skipSplit();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_undosplit", [this](const std::vector<std::string> &commands) {
        this->liveSplitModel.undoSplit();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
}

void LiveSplitComponent::render()
{
    ImGui::PushID(this);

    ImGui::Text("LiveSplit Remote Controller");
    ImGuiExtensions::BigSeparator();

    this->renderConnectionStatus();
    ImGuiExtensions::BigSpacing();

    this->renderRemoteControls();

    ImGui::PopID();
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

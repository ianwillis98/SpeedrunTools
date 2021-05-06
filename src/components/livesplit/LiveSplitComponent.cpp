#include "LiveSplitComponent.h"

LiveSplitComponent::LiveSplitComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponentBase(plugin),
          liveSplitModel(LiveSplitModel::getInstance(plugin))
{
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_connect", [this](const std::vector<std::string> &commands) {
        this->liveSplitModel.connect();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_disconnect", [this](const std::vector<std::string> &commands) {
        this->liveSplitModel.disconnect();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_startorsplit", [this](const std::vector<std::string> &commands) {
        this->liveSplitModel.startOrSplit();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_start", [this](const std::vector<std::string> &commands) {
        this->liveSplitModel.start();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_pause", [this](const std::vector<std::string> &commands) {
        this->liveSplitModel.pause();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_resume", [this](const std::vector<std::string> &commands) {
        this->liveSplitModel.resume();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_reset", [this](const std::vector<std::string> &commands) {
        this->liveSplitModel.reset();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_split", [this](const std::vector<std::string> &commands) {
        this->liveSplitModel.split();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_skipsplit", [this](const std::vector<std::string> &commands) {
        this->liveSplitModel.skipSplit();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_undosplit", [this](const std::vector<std::string> &commands) {
        this->liveSplitModel.undoSplit();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
}

void LiveSplitComponent::render()
{
    ImGui::PushID(this);

    ImGuiExtensions::BigSpacing();
    ImGui::Text("LiveSplit Remote Controller");

    ImGui::BulletText("Connection Status: ");
    ImGui::SameLine();
    if (this->liveSplitModel.isConnected())
        ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Connected");
    else if (this->liveSplitModel.isConnecting())
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Connecting %c", "|/-\\"[(int) (ImGui::GetTime() / 0.05f) & 3]);
    else
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Not Connected");

    ImGui::BulletText("Status Message: %s", this->liveSplitModel.getStatusMessage().c_str());
    ImGuiExtensions::BigSpacing();

    ImGui::Text("Remote Controls:");
    ImGui::Spacing();
    ImGuiExtensions::PushDisabledStyleIf(this->liveSplitModel.isConnecting());
    if (ImGui::Button(this->liveSplitModel.isConnected() ? "Reconnect" : "Connect"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->liveSplitModel.connect();
        });
    }
    ImGuiExtensions::PopDisabledStyleIf(this->liveSplitModel.isConnecting());

    if (this->liveSplitModel.isConnected())
    {
        ImGui::SameLine();
        if (ImGui::Button("Disconnect"))
        {
            this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
                this->liveSplitModel.disconnect();
            });
        }

        ImGui::Spacing();

        if (ImGui::Button("Start or Split"))
        {
            this->plugin->gameWrapper->Execute([&](GameWrapper *gw) {
                this->liveSplitModel.startOrSplit();
            });
        }

        ImGui::Spacing();

        if (ImGui::Button("Start"))
        {
            this->plugin->gameWrapper->Execute([&](GameWrapper *gw) {
                this->liveSplitModel.start();
            });
        }
        ImGui::SameLine();
        if (ImGui::Button("Pause"))
        {
            this->plugin->gameWrapper->Execute([&](GameWrapper *gw) {
                this->liveSplitModel.pause();
            });
        }
        ImGui::SameLine();
        if (ImGui::Button("Resume"))
        {
            this->plugin->gameWrapper->Execute([&](GameWrapper *gw) {
                this->liveSplitModel.resume();
            });
        }
        ImGui::SameLine();
        if (ImGui::Button("Reset"))
        {
            this->plugin->gameWrapper->Execute([&](GameWrapper *gw) {
                this->liveSplitModel.reset();
            });
        }

        ImGui::Spacing();

        if (ImGui::Button("Split"))
        {
            this->plugin->gameWrapper->Execute([&](GameWrapper *gw) {
                this->liveSplitModel.split();
            });
        }
        ImGui::SameLine();
        if (ImGui::Button("Skip Split"))
        {
            this->plugin->gameWrapper->Execute([&](GameWrapper *gw) {
                this->liveSplitModel.skipSplit();
            });
        }
        ImGui::SameLine();
        if (ImGui::Button("Undo Split"))
        {
            this->plugin->gameWrapper->Execute([&](GameWrapper *gw) {
                this->liveSplitModel.undoSplit();
            });
        }
    }
    ImGui::PopID();
}

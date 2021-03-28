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


LiveSplitComponent::LiveSplitComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponentBase(plugin),
          liveSplitClient(LiveSplitClient::getInstance()),
          feedbackMessage("Waiting for a connection to the LiveSplit server...")
{

}

void LiveSplitComponent::onLoad()
{
    this->plugin->cvarManager->registerNotifier(ConnectCVarName, [this](const std::vector<std::string> &commands) {
        this->connectAsync();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier(DisconnectCVarName, [this](const std::vector<std::string> &commands) {
        this->disconnect();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier(StartOrSplitCVarName, [this](const std::vector<std::string> &commands) {
        this->startOrSplit();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier(StartCVarName, [this](const std::vector<std::string> &commands) {
        this->start();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier(PauseCVarName, [this](const std::vector<std::string> &commands) {
        this->pause();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier(ResumeCVarName, [this](const std::vector<std::string> &commands) {
        this->resume();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier(ResetCVarName, [this](const std::vector<std::string> &commands) {
        this->reset();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier(SplitCVarName, [this](const std::vector<std::string> &commands) {
        this->split();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier(SkipSplitCVarName, [this](const std::vector<std::string> &commands) {
        this->skipSplit();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier(UndoSplitCVarName, [this](const std::vector<std::string> &commands) {
        this->undoSplit();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
}

void LiveSplitComponent::render()
{
    ImGui::PushID(this);
    ImGuiExtensions::BigSpacing();

    ImGui::Text("LiveSplit Remote Controller");
    ImGui::BulletText("Connection Status: ");
    ImGui::SameLine();
    switch (this->liveSplitClient.getConnectionState())
    {
        case ConnectionState::Connected:
            ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Connected");
            break;
        case ConnectionState::Connecting:
            ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Connecting %c", "|/-\\"[(int) (ImGui::GetTime() / 0.05f) & 3]);
            break;
        case ConnectionState::NotConnected:
            ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Not Connected");
            break;
    }
    ImGui::BulletText("Feedback Message: %s", this->feedbackMessage.c_str());

    ImGuiExtensions::BigSpacing();

    ImGui::Text("Remote Controls:");
    ImGui::Spacing();
    ImGuiExtensions::PushDisabledStyleIf(this->liveSplitClient.isConnecting());
    if (ImGui::Button(this->liveSplitClient.isConnected() ? "Reconnect" : "Connect"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->connectAsync();
        });
    }
    ImGuiExtensions::PopDisabledStyleIf(this->liveSplitClient.isConnecting());

    if (this->liveSplitClient.isConnected())
    {
        ImGui::SameLine();
        if (ImGui::Button("Disconnect"))
        {
            this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
                this->disconnect();
            });
        }

        ImGui::Spacing();

        if (ImGui::Button("Start or Split"))
        {
            this->plugin->gameWrapper->Execute([&](GameWrapper *gw) {
                this->startOrSplit();
            });
        }

        ImGui::Spacing();

        if (ImGui::Button("Start"))
        {
            this->plugin->gameWrapper->Execute([&](GameWrapper *gw) {
                this->start();
            });
        }
        ImGui::SameLine();
        if (ImGui::Button("Pause"))
        {
            this->plugin->gameWrapper->Execute([&](GameWrapper *gw) {
                this->pause();
            });
        }
        ImGui::SameLine();
        if (ImGui::Button("Resume"))
        {
            this->plugin->gameWrapper->Execute([&](GameWrapper *gw) {
                this->resume();
            });
        }
        ImGui::SameLine();
        if (ImGui::Button("Reset"))
        {
            this->plugin->gameWrapper->Execute([&](GameWrapper *gw) {
                this->reset();
            });
        }

        ImGui::Spacing();

        if (ImGui::Button("Split"))
        {
            this->plugin->gameWrapper->Execute([&](GameWrapper *gw) {
                this->split();
            });
        }
        ImGui::SameLine();
        if (ImGui::Button("Skip Split"))
        {
            this->plugin->gameWrapper->Execute([&](GameWrapper *gw) {
                this->skipSplit();
            });
        }
        ImGui::SameLine();
        if (ImGui::Button("Undo Split"))
        {
            this->plugin->gameWrapper->Execute([&](GameWrapper *gw) {
                this->undoSplit();
            });
        }
    }
    ImGui::PopID();
}

void LiveSplitComponent::connectAsync()
{
    this->feedbackMessage = "Attempting to establish a connection with the LiveSplit Server...";
    this->log(this->feedbackMessage);
    this->liveSplitClient.connectAsync("localhost", "16834", [this](const int &errorCode, const std::string &errorMessage) {
        this->feedbackMessage = (errorCode == 0) ? "Connection established with the LiveSplit Server." :
                                "Error while connecting to the LiveSplit Server (" + std::to_string(errorCode) + ") \"" + errorMessage + "\"." +
                                "\nMake sure the LiveSplit Server is running and open on port 16834.";
        this->log(this->feedbackMessage);
    });
}

void LiveSplitComponent::disconnect()
{
    this->liveSplitClient.disconnect([this](const int &errorCode, const std::string &errorMessage) {
        this->feedbackMessage = (errorCode == 0) ? "Disconnected from the LiveSplit Server." :
                                "Error while disconnecting from the LiveSplit Server (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->log(this->feedbackMessage);
    });
}

void LiveSplitComponent::startOrSplit()
{
    this->liveSplitClient.startOrSplit([this](const int &errorCode, const std::string &errorMessage) {
        this->feedbackMessage = (errorCode == 0) ? "'startOrSplit' message was successfully sent." :
                                "Error while sending message 'startOrSplit' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->log(this->feedbackMessage);
    });
}

void LiveSplitComponent::start()
{
    this->liveSplitClient.start([this](const int &errorCode, const std::string &errorMessage) {
        this->feedbackMessage = (errorCode == 0) ? "'start' message was successfully sent." :
                                "Error while sending message 'start' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->log(this->feedbackMessage);
    });
}

void LiveSplitComponent::pause()
{
    this->liveSplitClient.pause([this](const int &errorCode, const std::string &errorMessage) {
        this->feedbackMessage = (errorCode == 0) ? "'pause' message was successfully sent." :
                                "Error while sending message 'pause' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->log(this->feedbackMessage);
    });
}

void LiveSplitComponent::resume()
{

    this->liveSplitClient.resume([this](const int &errorCode, const std::string &errorMessage) {
        this->feedbackMessage = (errorCode == 0) ? "'resume' message was successfully sent." :
                                "Error while sending message 'resume' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->log(this->feedbackMessage);
    });
}

void LiveSplitComponent::reset()
{
    this->liveSplitClient.reset([this](const int &errorCode, const std::string &errorMessage) {
        this->feedbackMessage = (errorCode == 0) ? "'reset' message was successfully sent." :
                                "Error while sending message 'reset' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->log(this->feedbackMessage);
    });
}

void LiveSplitComponent::split()
{
    this->liveSplitClient.split([this](const int &errorCode, const std::string &errorMessage) {
        this->feedbackMessage = (errorCode == 0) ? "'split' message was successfully sent." :
                                "Error while sending message 'split' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->log(this->feedbackMessage);
    });
}

void LiveSplitComponent::skipSplit()
{
    this->liveSplitClient.skipSplit([this](const int &errorCode, const std::string &errorMessage) {
        this->feedbackMessage = (errorCode == 0) ? "'skipSplit' message was successfully sent." :
                                "Error while sending message 'skipSplit' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->log(this->feedbackMessage);
    });
}

void LiveSplitComponent::undoSplit()
{

    this->liveSplitClient.undoSplit([this](const int &errorCode, const std::string &errorMessage) {
        this->feedbackMessage = (errorCode == 0) ? "'undoSplit' message was successfully sent." :
                                "Error while sending message 'undoSplit' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->log(this->feedbackMessage);
    });
}

void LiveSplitComponent::log(const std::string &message)
{
    this->plugin->cvarManager->log("LiveSplit Client: " + message);
    this->plugin->gameWrapper->Execute([this, message](GameWrapper *gw) {
        this->plugin->gameWrapper->LogToChatbox("LiveSplit Client: " + message, "SPEEDRUNTOOLS");
    });
}

std::string LiveSplitComponent::getConnectionStatusAsString()
{
    switch (this->liveSplitClient.getConnectionState())
    {
        case ConnectionState::Connected:
            ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Yellow");
            return "Connected";
        case ConnectionState::Connecting:
            return "Connecting " + std::string(1, "|/-\\"[(int) (ImGui::GetTime() / 0.05f) & 3]);
        case ConnectionState::NotConnected:
            return "Not Connected";
        default:
            return "Unknown Connection Status";

    }
}

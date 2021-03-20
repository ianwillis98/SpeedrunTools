#include "LiveSplitRemoteComponent.h"

LiveSplitRemoteComponent::LiveSplitRemoteComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponentBase(plugin),
          liveSplitClient(LiveSplitClient::getInstance()),
          feedbackMessage("Waiting for a connection to the LiveSplit server...")
{

}

void LiveSplitRemoteComponent::onLoad()
{
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_connect", [this](const std::vector<std::string> &commands) {
        this->connectAsync();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_disconnect", [this](const std::vector<std::string> &commands) {
        this->disconnect();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_startorsplit", [this](const std::vector<std::string> &commands) {
        this->startOrSplit();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_start", [this](const std::vector<std::string> &commands) {
        this->start();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_pause", [this](const std::vector<std::string> &commands) {
        this->pause();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_resume", [this](const std::vector<std::string> &commands) {
        this->resume();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_reset", [this](const std::vector<std::string> &commands) {
        this->reset();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_split", [this](const std::vector<std::string> &commands) {
        this->split();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_skipsplit", [this](const std::vector<std::string> &commands) {
        this->skipSplit();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_undosplit", [this](const std::vector<std::string> &commands) {
        this->undoSplit();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
}

void LiveSplitRemoteComponent::render()
{
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
}

void LiveSplitRemoteComponent::connectAsync()
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

void LiveSplitRemoteComponent::disconnect()
{
    this->liveSplitClient.disconnect([this](const int &errorCode, const std::string &errorMessage) {
        this->feedbackMessage = (errorCode == 0) ? "Disconnected from the LiveSplit Server." :
                                "Error while disconnecting from the LiveSplit Server (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->log(this->feedbackMessage);
    });
}

void LiveSplitRemoteComponent::startOrSplit()
{
    this->liveSplitClient.startOrSplit([this](const int &errorCode, const std::string &errorMessage) {
        this->feedbackMessage = (errorCode == 0) ? "'startOrSplit' message was successfully sent." :
                                "Error while sending message 'startOrSplit' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->log(this->feedbackMessage);
    });
}

void LiveSplitRemoteComponent::start()
{
    this->liveSplitClient.start([this](const int &errorCode, const std::string &errorMessage) {
        this->feedbackMessage = (errorCode == 0) ? "'start' message was successfully sent." :
                                "Error while sending message 'start' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->log(this->feedbackMessage);
    });
}

void LiveSplitRemoteComponent::pause()
{
    this->liveSplitClient.pause([this](const int &errorCode, const std::string &errorMessage) {
        this->feedbackMessage = (errorCode == 0) ? "'pause' message was successfully sent." :
                                "Error while sending message 'pause' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->log(this->feedbackMessage);
    });
}

void LiveSplitRemoteComponent::resume()
{

    this->liveSplitClient.resume([this](const int &errorCode, const std::string &errorMessage) {
        this->feedbackMessage = (errorCode == 0) ? "'resume' message was successfully sent." :
                                "Error while sending message 'resume' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->log(this->feedbackMessage);
    });
}

void LiveSplitRemoteComponent::reset()
{
    this->liveSplitClient.reset([this](const int &errorCode, const std::string &errorMessage) {
        this->feedbackMessage = (errorCode == 0) ? "'reset' message was successfully sent." :
                                "Error while sending message 'reset' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->log(this->feedbackMessage);
    });
}

void LiveSplitRemoteComponent::split()
{
    this->liveSplitClient.split([this](const int &errorCode, const std::string &errorMessage) {
        this->feedbackMessage = (errorCode == 0) ? "'split' message was successfully sent." :
                                "Error while sending message 'split' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->log(this->feedbackMessage);
    });
}

void LiveSplitRemoteComponent::skipSplit()
{
    this->liveSplitClient.skipSplit([this](const int &errorCode, const std::string &errorMessage) {
        this->feedbackMessage = (errorCode == 0) ? "'skipSplit' message was successfully sent." :
                                "Error while sending message 'skipSplit' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->log(this->feedbackMessage);
    });
}

void LiveSplitRemoteComponent::undoSplit()
{

    this->liveSplitClient.undoSplit([this](const int &errorCode, const std::string &errorMessage) {
        this->feedbackMessage = (errorCode == 0) ? "'undoSplit' message was successfully sent." :
                                "Error while sending message 'undoSplit' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->log(this->feedbackMessage);
    });
}

void LiveSplitRemoteComponent::log(const std::string &message)
{
    this->plugin->cvarManager->log("LiveSplit Client: " + message);
    this->plugin->gameWrapper->Execute([this, message](GameWrapper *gw) {
        //this->plugin->gameWrapper->LogToChatbox("LiveSplit Client: " + message, "SPEEDRUNTOOLS");
    });
}

std::string LiveSplitRemoteComponent::getConnectionStatusAsString()
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

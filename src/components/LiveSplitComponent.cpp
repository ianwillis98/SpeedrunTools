#include "LiveSplitComponent.h"

LiveSplitComponent::LiveSplitComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponent(plugin), liveSplitClient(LiveSplitClient::getInstance()), feedbackMessage("Waiting for connect..."),
          autoSplitterManager(AutoSplitterManager::getInstance(plugin)), currentMap(""), isCurrentMapSupported(false),
          isAutoSplitterRunning(false)
{

}

std::string LiveSplitComponent::title()
{
    return "LiveSplit & Auto Splitter";
}

void LiveSplitComponent::onLoad()
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

void LiveSplitComponent::render()
{
    ImGuiExtensions::BigSpacing();

    this->renderLiveSplitClient();

    if (this->liveSplitClient.getConnectionState() == ConnectionState::Connected)
    {
        ImGuiExtensions::BigSeparator();

        this->renderAutoSplitter();
    }

}

void LiveSplitComponent::onEvent(std::string eventName, bool post, void *params)
{
    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && !post)
    {
        if (!this->plugin->gameWrapper->IsInGame()) return;

        this->currentMap = this->plugin->gameWrapper->GetCurrentMap();
        this->isCurrentMapSupported = this->autoSplitterManager.isCurrentMapSupported();
        if (!this->isCurrentMapSupported) this->isAutoSplitterRunning = false;

        if (this->isAutoSplitterRunning)
        {
            if (this->autoSplitterManager.update())
            {
                if (this->autoSplitterManager.shouldStartTimer())
                {
                    this->start();
                }
                if (this->autoSplitterManager.shouldSplitTimer())
                {
                    this->split();
                }
                if (this->autoSplitterManager.shouldResetTimer())
                {
                    this->reset();
                }
            }
        }
    }
}

void LiveSplitComponent::renderLiveSplitClient()
{
    std::string connectionStateString;
    ConnectionState connectionState = this->liveSplitClient.getConnectionState();
    switch (connectionState)
    {
        case ConnectionState::Connected:
            connectionStateString = "Connected";
            break;
        case ConnectionState::Connecting:
            connectionStateString = "Connecting ";
            connectionStateString += "|/-\\"[(int) (ImGui::GetTime() / 0.05f) & 3];
            break;
        case ConnectionState::NotConnected:
            connectionStateString = "Not Connected";
            break;
    }
    ImGui::Spacing();
    ImGui::Text("LiveSplit Client: %s", connectionStateString.c_str());
    ImGui::Spacing();
    ImGui::Text("%s", this->feedbackMessage.c_str());
    ImGui::Spacing();

    ImGuiExtensions::PushDisabledStyleIf(connectionState == ConnectionState::Connecting);
    if (ImGui::Button("Connect"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->connectAsync();
        });
    }
    ImGuiExtensions::PopDisabledStyleIf(connectionState == ConnectionState::Connecting);

    if (liveSplitClient.getConnectionState() == ConnectionState::Connected)
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

void LiveSplitComponent::renderAutoSplitter()
{
    if (!this->plugin->gameWrapper->IsInGame())
    {
        ImGui::Text("Auto Splitter: Waiting for player to load a map...");
    }
    else
    {
        ImGui::Text("Current Map: %s", this->currentMap.c_str());
        ImGui::Text("Is current map supported? %s", std::to_string(this->isCurrentMapSupported).c_str());
        if (this->isCurrentMapSupported)
        {
            ImGui::Checkbox("Turn on/off auto splitter", &this->isAutoSplitterRunning);
        }
    }
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

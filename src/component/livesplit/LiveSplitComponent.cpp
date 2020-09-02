#include "LiveSplitComponent.h"
#include "../../utils/ImGuiExtensions.h"

LiveSplitComponent::LiveSplitComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponent(plugin), liveSplitClient(LiveSplitClient::getInstance()), feedbackMessage("Waiting for connection...")
{

}

void LiveSplitComponent::onLoad()
{

}

void LiveSplitComponent::onUnload()
{

}

void LiveSplitComponent::render()
{
    ImGui::Text("Interact with LiveSplit through LiveSplit Server");

    ImGui::Spacing();

    ImGui::Text("Connection Status:");
    ImGui::SameLine();
    std::string connectionStateString;
    ConnectionState connectionState = this->liveSplitClient.getConnectionState();
    switch (connectionState)
    {
        case ConnectionState::Connected:
            connectionStateString = "Connected";
            break;
        case ConnectionState::Connecting:
            connectionStateString = "Connecting";
            break;
        case ConnectionState::NotConnected:
            connectionStateString = "Not Connected";
            break;
    }
    ImGui::Text("%s", connectionStateString.c_str());
    if (connectionState == ConnectionState::Connecting)
    {
        ImGui::SameLine();
        ImGui::Text("%c", "|/-\\"[(int) (ImGui::GetTime() / 0.05f) & 3]);
    }

    ImGui::Spacing();

    ImGui::Text("Feedback message: %s", this->feedbackMessage.c_str());

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

    ImGui::Spacing();
}

void LiveSplitComponent::connectAsync()
{
    this->feedbackMessage = "Attempting to establish a connection with the LiveSplit Server...";

    try
    {
        this->liveSplitClient.connectAsync("localhost", "16834", [this](const int &errorCode, const std::string &errorMessage) {
            this->plugin->gameWrapper->Execute([this, errorCode, errorMessage](GameWrapper *gw) {
                if (errorCode == 0)
                {
                    this->feedbackMessage = "Connection established with the LiveSplit Server.";
                }
                else
                {
                    std::string ecs = std::to_string(errorCode);
                    this->feedbackMessage = "Error while connecting to the LiveSplit Server (" + ecs + ") \"" + errorMessage + "\".";
                    this->feedbackMessage += "\nMake sure the LiveSplit Server is running and open on port 16834.";
                }
            });
        });
    }
    catch (const std::exception &e)
    {
        this->feedbackMessage = "LiveSplitToolkit: Error while setting up the connection \"" + std::string(e.what()) + "\".";
    }
}

void LiveSplitComponent::disconnect()
{
    try
    {
        this->liveSplitClient.disconnect();
        this->feedbackMessage = "Disconnected from the LiveSplit Server.";
    }
    catch (const std::exception &e)
    {
        this->feedbackMessage = "Error while disconnecting \"" + std::string(e.what()) + "\".";
    }
}

void LiveSplitComponent::startOrSplit()
{
    try
    {
        this->liveSplitClient.startOrSplit([this](const int &errorCode, const std::string &errorMessage) {
            this->plugin->gameWrapper->Execute([this, errorCode, errorMessage](GameWrapper *gw) {
                if (errorCode == 0)
                {
                    this->feedbackMessage = "'startOrSplit' message was successfully sent.";
                }
                else
                {
                    std::string ecs = std::to_string(errorCode);
                    this->feedbackMessage = "Error while sending message 'startOrSplit' (" + ecs + ") \"" + errorMessage + "\".";
                }
            });
        });
    }
    catch (const std::exception &e)
    {
        this->feedbackMessage = "Error while trying to send a message to the LiveSplit Server \"" + std::string(e.what()) + "\".";
    }
}

void LiveSplitComponent::start()
{
    try
    {
        this->liveSplitClient.start([this](const int &errorCode, const std::string &errorMessage) {
            this->plugin->gameWrapper->Execute([this, errorCode, errorMessage](GameWrapper *gw) {
                if (errorCode == 0)
                {
                    this->feedbackMessage = "'start' message was successfully sent.";
                }
                else
                {
                    std::string ecs = std::to_string(errorCode);
                    this->feedbackMessage = "Error while sending message 'start' (" + ecs + ") \"" + errorMessage + "\".";
                }
            });
        });
    }
    catch (const std::exception &e)
    {
        this->feedbackMessage = "Error while trying to send a message to the LiveSplit Server \"" + std::string(e.what()) + "\".";
    }
}

void LiveSplitComponent::pause()
{
    try
    {
        this->liveSplitClient.pause([this](const int &errorCode, const std::string &errorMessage) {
            this->plugin->gameWrapper->Execute([this, errorCode, errorMessage](GameWrapper *gw) {
                if (errorCode == 0)
                {
                    this->feedbackMessage = "'pause' message was successfully sent.";
                }
                else
                {
                    std::string ecs = std::to_string(errorCode);
                    this->feedbackMessage = "Error while sending message 'pause' (" + ecs + ") \"" + errorMessage + "\".";
                }
            });
        });
    }
    catch (const std::exception &e)
    {
        this->feedbackMessage = "Error while trying to send a message to the LiveSplit Server \"" + std::string(e.what()) + "\".";
    }
}

void LiveSplitComponent::resume()
{
    try
    {
        this->liveSplitClient.resume([this](const int &errorCode, const std::string &errorMessage) {
            this->plugin->gameWrapper->Execute([this, errorCode, errorMessage](GameWrapper *gw) {
                if (errorCode == 0)
                {
                    this->feedbackMessage = "'resume' message was successfully sent.";
                }
                else
                {
                    std::string ecs = std::to_string(errorCode);
                    this->feedbackMessage = "Error while sending message 'resume' (" + ecs + ") \"" + errorMessage + "\".";
                }
            });
        });
    }
    catch (const std::exception &e)
    {
        this->feedbackMessage = "Error while trying to send a message to the LiveSplit Server \"" + std::string(e.what()) + "\".";
    }
}

void LiveSplitComponent::reset()
{
    try
    {
        this->liveSplitClient.reset([this](const int &errorCode, const std::string &errorMessage) {
            this->plugin->gameWrapper->Execute([this, errorCode, errorMessage](GameWrapper *gw) {
                if (errorCode == 0)
                {
                    this->feedbackMessage = "'reset' message was successfully sent.";
                }
                else
                {
                    std::string ecs = std::to_string(errorCode);
                    this->feedbackMessage = "Error while sending message 'reset' (" + ecs + ") \"" + errorMessage + "\".";
                }
            });
        });
    }
    catch (const std::exception &e)
    {
        this->feedbackMessage = "Error while trying to send a message to the LiveSplit Server \"" + std::string(e.what()) + "\".";
    }
}

void LiveSplitComponent::split()
{
    try
    {
        this->liveSplitClient.split([this](const int &errorCode, const std::string &errorMessage) {
            this->plugin->gameWrapper->Execute([this, errorCode, errorMessage](GameWrapper *gw) {
                if (errorCode == 0)
                {
                    this->feedbackMessage = "'split' message was successfully sent.";
                }
                else
                {
                    std::string ecs = std::to_string(errorCode);
                    this->feedbackMessage = "Error while sending message 'split' (" + ecs + ") \"" + errorMessage + "\".";
                }
            });
        });
    }
    catch (const std::exception &e)
    {
        this->feedbackMessage = "Error while trying to send a message to the LiveSplit Server \"" + std::string(e.what()) + "\".";
    }
}

void LiveSplitComponent::skipSplit()
{
    try
    {
        this->liveSplitClient.skipSplit([this](const int &errorCode, const std::string &errorMessage) {
            this->plugin->gameWrapper->Execute([this, errorCode, errorMessage](GameWrapper *gw) {
                if (errorCode == 0)
                {
                    this->feedbackMessage = "'skipSplit' message was successfully sent.";
                }
                else
                {
                    std::string ecs = std::to_string(errorCode);
                    this->feedbackMessage = "Error while sending message 'skipSplit' (" + ecs + ") \"" + errorMessage + "\".";
                }
            });
        });
    }
    catch (const std::exception &e)
    {
        this->feedbackMessage = "Error while trying to send a message to the LiveSplit Server \"" + std::string(e.what()) + "\".";
    }
}

void LiveSplitComponent::undoSplit()
{
    try
    {
        this->liveSplitClient.undoSplit([this](const int &errorCode, const std::string &errorMessage) {
            this->plugin->gameWrapper->Execute([this, errorCode, errorMessage](GameWrapper *gw) {
                if (errorCode == 0)
                {
                    this->feedbackMessage = "'undoSplit' message was successfully sent.";
                }
                else
                {
                    std::string ecs = std::to_string(errorCode);
                    this->feedbackMessage = "Error while sending message 'undoSplit' (" + ecs + ") \"" + errorMessage + "\".";
                }
            });
        });
    }
    catch (const std::exception &e)
    {
        this->feedbackMessage = "Error while trying to send a message to the LiveSplit Server \"" + std::string(e.what()) + "\".";
    }
}

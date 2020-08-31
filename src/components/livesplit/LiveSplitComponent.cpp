#include <map>
#include <bakkesmod/wrappers/kismet/SequenceWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceVariableWrapper.h>
#include "LiveSplitComponent.h"
#include "../../utils/ImGuiExtensions.h"

LiveSplitComponent::LiveSplitComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponent(plugin), liveSplitClient(LiveSplitClient::getInstance())
{

}

void LiveSplitComponent::onLoad()
{
    CVarWrapper componentEnabled = this->plugin->cvarManager->registerCvar("st_livesplit_enabled", "1", "Is livesplit enabled");
    componentEnabled.addOnValueChanged([this](const std::string &oldValue, const CVarWrapper &cvar) {
        this->onComponentEnabledChanged();
    });

    this->plugin->cvarManager->registerNotifier("st_livesplit_connect", [this](const std::vector<std::string> &commands) {
        this->connectAsync();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("st_livesplit_startorsplit", [this](const std::vector<std::string> &commands) {
        this->startOrSplit();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("st_livesplit_start", [this](const std::vector<std::string> &commands) {
        this->start();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("st_livesplit_pause", [this](const std::vector<std::string> &commands) {
        this->pause();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("st_livesplit_resume", [this](const std::vector<std::string> &commands) {
        this->resume();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("st_livesplit_reset", [this](const std::vector<std::string> &commands) {
        this->reset();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("st_livesplit_split", [this](const std::vector<std::string> &commands) {
        this->split();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("st_livesplit_skipsplit", [this](const std::vector<std::string> &commands) {
        this->skipSplit();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("st_livesplit_undosplit", [this](const std::vector<std::string> &commands) {
        this->undoSplit();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
}

void LiveSplitComponent::onUnload()
{

}

void LiveSplitComponent::render()
{
    bool isComponentEnabled = this->isComponentEnabled();
    ImGuiExtensions::PushDisabledStyleIf(this->liveSplitClient.connectionState == ConnectionState::Connecting);
    if (ImGui::Checkbox("Interact with LiveSplit through a LiveSplit Server", &isComponentEnabled))
    {
        this->plugin->gameWrapper->Execute([this, isComponentEnabled](GameWrapper *gw) {
            this->setComponentEnabled(isComponentEnabled);
        });
    }
    ImGuiExtensions::PopDisabledStyleIf(this->liveSplitClient.connectionState == ConnectionState::Connecting);

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

    ImGuiExtensions::PushDisabledStyleIf(!isComponentEnabled);

    ImGuiExtensions::PushDisabledStyleIf(isComponentEnabled && connectionState == ConnectionState::Connecting);
    if (ImGui::Button("Connect"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->connectAsync();
        });
    }
    ImGuiExtensions::PopDisabledStyleIf(isComponentEnabled && connectionState == ConnectionState::Connecting);

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
                liveSplitClient.start();
            });
        }
        ImGui::SameLine();
        if (ImGui::Button("Pause"))
        {
            this->plugin->gameWrapper->Execute([&](GameWrapper *gw) {
                liveSplitClient.pause();
            });
        }
        ImGui::SameLine();
        if (ImGui::Button("Resume"))
        {
            this->plugin->gameWrapper->Execute([&](GameWrapper *gw) {
                liveSplitClient.resume();
            });
        }
        ImGui::SameLine();
        if (ImGui::Button("Reset"))
        {
            this->plugin->gameWrapper->Execute([&](GameWrapper *gw) {
                liveSplitClient.reset();
            });
        }

        ImGui::Spacing();

        if (ImGui::Button("Split"))
        {
            this->plugin->gameWrapper->Execute([&](GameWrapper *gw) {
                liveSplitClient.split();
            });
        }
        ImGui::SameLine();
        if (ImGui::Button("Skip Split"))
        {
            this->plugin->gameWrapper->Execute([&](GameWrapper *gw) {
                liveSplitClient.skipSplit();
            });
        }
        ImGui::SameLine();
        if (ImGui::Button("Undo Split"))
        {
            this->plugin->gameWrapper->Execute([&](GameWrapper *gw) {
                liveSplitClient.undoSplit();
            });
        }
    }

    ImGuiExtensions::PopDisabledStyleIf(!isComponentEnabled);

    ImGui::Spacing();
}

void LiveSplitComponent::connectAsync()
{
    if (!this->isComponentEnabled()) return;

    this->plugin->cvarManager->log("LiveSplitToolkit: Attempting to establish a connection with the LiveSplit Server...");

    try
    {
        this->liveSplitClient.connectAsync("localhost", "16834", [this](const int &errorCode, const std::string &errorMessage) {
            this->plugin->gameWrapper->Execute([this, errorCode, errorMessage](GameWrapper *gw) {
                if (errorCode == 0)
                {
                    this->plugin->cvarManager->log("LiveSplitToolkit: Connection established with the LiveSplit Server.");
                }
                else
                {
                    std::string ecs = std::to_string(errorCode);
                    this->plugin->cvarManager->log(
                            "LiveSplitToolkit: Error while connecting to the LiveSplit Server (" + ecs + ") \"" + errorMessage + "\".");
                    this->plugin->cvarManager->log("LiveSplitToolkit: Make sure the LiveSplit Server is running and open on port 16834.");
                }
            });
        });
    }
    catch (const std::exception &e)
    {
        this->plugin->cvarManager->log("LiveSplitToolkit: Error while setting up the connection \"" + std::string(e.what()) + "\".");
    }
}

void LiveSplitComponent::disconnect()
{
    if (!this->isComponentEnabled()) return;

    try
    {
        this->liveSplitClient.disconnect();
    }
    catch (const std::exception &e)
    {
        this->plugin->cvarManager->log("LiveSplitToolkit: Error while disconnecting \"" + std::string(e.what()) + "\".");
    }
}

void LiveSplitComponent::startOrSplit()
{
    if (!this->isComponentEnabled()) return;

    try
    {
        this->liveSplitClient.startOrSplit();
    }
    catch (const std::exception &e)
    {
        this->plugin->cvarManager->log("LiveSplitToolkit: Error while trying to send the command 'startorsplit' \"" + std::string(e.what()) + "\".");
    }
}

void LiveSplitComponent::start()
{
    if (!this->isComponentEnabled()) return;

    try
    {
        this->liveSplitClient.start();
    }
    catch (const std::exception &e)
    {
        this->plugin->cvarManager->log("LiveSplitToolkit: Error while trying to send the command 'start' \"" + std::string(e.what()) + "\".");
    }
}

void LiveSplitComponent::pause()
{
    if (!this->isComponentEnabled()) return;

    try
    {
        this->liveSplitClient.pause();
    }
    catch (const std::exception &e)
    {
        this->plugin->cvarManager->log("LiveSplitToolkit: Error while trying to send the command 'pause' \"" + std::string(e.what()) + "\".");
    }
}

void LiveSplitComponent::resume()
{
    if (!this->isComponentEnabled()) return;

    try
    {
        this->liveSplitClient.resume();
    }
    catch (const std::exception &e)
    {
        this->plugin->cvarManager->log("LiveSplitToolkit: Error while trying to send the command 'resume' \"" + std::string(e.what()) + "\".");
    }
}

void LiveSplitComponent::reset()
{
    if (!this->isComponentEnabled()) return;

    try
    {
        this->liveSplitClient.reset();
    }
    catch (const std::exception &e)
    {
        this->plugin->cvarManager->log("LiveSplitToolkit: Error while trying to send the command 'reset' \"" + std::string(e.what()) + "\".");
    }
}

void LiveSplitComponent::split()
{
    if (!this->isComponentEnabled()) return;

    try
    {
        this->liveSplitClient.split();
    }
    catch (const std::exception &e)
    {
        this->plugin->cvarManager->log("LiveSplitToolkit: Error while trying to send the command 'split' \"" + std::string(e.what()) + "\".");
    }
}

void LiveSplitComponent::skipSplit()
{
    if (!this->isComponentEnabled()) return;

    try
    {
        this->liveSplitClient.skipSplit();
    }
    catch (const std::exception &e)
    {
        this->plugin->cvarManager->log("LiveSplitToolkit: Error while trying to send the command 'skipSplit' \"" + std::string(e.what()) + "\".");
    }
}

void LiveSplitComponent::undoSplit()
{
    if (!this->isComponentEnabled()) return;

    try
    {
        this->liveSplitClient.undoSplit();
    }
    catch (const std::exception &e)
    {
        this->plugin->cvarManager->log("LiveSplitToolkit: Error while trying to send the command 'undoSplit' \"" + std::string(e.what()) + "\".");
    }
}

bool LiveSplitComponent::isComponentEnabled()
{
    return this->plugin->cvarManager->getCvar("st_livesplit_enabled").getBoolValue();
}

void LiveSplitComponent::setComponentEnabled(bool enabled)
{
    if (this->liveSplitClient.connectionState == ConnectionState::Connecting)
    {
        this->plugin->cvarManager->log("LiveSplitToolkit: cannot disable component while trying to connect.");
        return;
    }

    this->plugin->cvarManager->getCvar("st_livesplit_enabled").setValue(enabled);
}

void LiveSplitComponent::onComponentEnabledChanged()
{
    if (!this->isComponentEnabled())
    {
        try
        {
            this->liveSplitClient.disconnect();
        }
        catch (const std::exception &e)
        {
            this->plugin->cvarManager->log("LiveSplitToolkit: Error while disconnecting \"" + std::string(e.what()) + "\".");
        }
    }
}

#include "LiveSplitToolkit.h"

LiveSplitToolkit::LiveSplitToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginToolkit(plugin), liveSplitClient(LiveSplitClient::getInstance()), liveSplitComponent(plugin)
{

}

std::string LiveSplitToolkit::title()
{
    return "LiveSplit";
}

void LiveSplitToolkit::onLoad()
{
    this->liveSplitComponent.onLoad();

    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_connect", [this](const std::vector<std::string> &commands) {
        this->onConnect();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_disconnect", [this](const std::vector<std::string> &commands) {
        this->onDisconnect();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_startorsplit", [this](const std::vector<std::string> &commands) {
        this->onStartOrSplit();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_start", [this](const std::vector<std::string> &commands) {
        this->onStart();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_pause", [this](const std::vector<std::string> &commands) {
        this->onPause();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_resume", [this](const std::vector<std::string> &commands) {
        this->onResume();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_reset", [this](const std::vector<std::string> &commands) {
        this->onReset();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_split", [this](const std::vector<std::string> &commands) {
        this->onSplit();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_skipsplit", [this](const std::vector<std::string> &commands) {
        this->onSkipSplit();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("speedrun_livesplit_undosplit", [this](const std::vector<std::string> &commands) {
        this->onUndoSplit();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
}

void LiveSplitToolkit::onUnload()
{
    this->liveSplitComponent.onUnload();
}

void LiveSplitToolkit::render()
{
    ImGui::Spacing();

    ImGui::Text("NOTE: You must have both LiveSplit AND LiveSplit Server installed for this to work");

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    this->liveSplitComponent.render();
}

void LiveSplitToolkit::onConnect()
{
    this->log("Attempting to establish a connection with the LiveSplit Server...");

    this->liveSplitClient.connectAsync("localhost", "16834", [this](const int &errorCode, const std::string &errorMessage) {
        if (errorCode == 0)
        {
            this->log("Connection established with the LiveSplit Server.");
        }
        else
        {
            this->log("Error while connecting to the LiveSplit Server (" + std::to_string(errorCode) + ") " + errorMessage + ".");
            this->log("Make sure the LiveSplit Server is running and open on port 16834.");
        }
    });
}

void LiveSplitToolkit::onDisconnect()
{
    this->liveSplitClient.disconnect([this](const int &errorCode, const std::string &errorMessage) {
        if (errorCode == 0)
        {
            this->log("Disconnected from the LiveSplit Server.");
        }
        else
        {
            this->log("Error while disconnecting from the LiveSplit Server (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".");
        }
    });
}

void LiveSplitToolkit::onStartOrSplit()
{
    this->liveSplitClient.startOrSplit([this](const int &errorCode, const std::string &errorMessage) {
        if (errorCode == 0)
        {
            this->log("'startOrSplit' message was successfully sent.");
        }
        else
        {
            this->log("Error while sending message 'startOrSplit' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".");
        }
    });
}

void LiveSplitToolkit::onStart()
{
    this->liveSplitClient.start([this](const int &errorCode, const std::string &errorMessage) {
        if (errorCode == 0)
        {
            this->log("'start' message was successfully sent.");
        }
        else
        {
            this->log("Error while sending message 'start' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".");
        }
    });
}

void LiveSplitToolkit::onPause()
{
    this->liveSplitClient.pause([this](const int &errorCode, const std::string &errorMessage) {
        if (errorCode == 0)
        {
            this->log("'pause' message was successfully sent.");
        }
        else
        {
            this->log("Error while sending message 'pause' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".");
        }
    });
}

void LiveSplitToolkit::onResume()
{
    this->liveSplitClient.resume([this](const int &errorCode, const std::string &errorMessage) {
        if (errorCode == 0)
        {
            this->log("'resume' message was successfully sent.");
        }
        else
        {
            this->log("Error while sending message 'resume' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".");
        }
    });
}

void LiveSplitToolkit::onReset()
{
    this->liveSplitClient.reset([this](const int &errorCode, const std::string &errorMessage) {
        if (errorCode == 0)
        {
            this->log("'reset' message was successfully sent.");
        }
        else
        {
            this->log("Error while sending message 'reset' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".");
        }
    });
}

void LiveSplitToolkit::onSplit()
{
    this->liveSplitClient.split([this](const int &errorCode, const std::string &errorMessage) {
        if (errorCode == 0)
        {
            this->log("'split' message was successfully sent.");
        }
        else
        {
            this->log("Error while sending message 'split' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".");
        }
    });
}

void LiveSplitToolkit::onSkipSplit()
{
    this->liveSplitClient.skipSplit([this](const int &errorCode, const std::string &errorMessage) {
        if (errorCode == 0)
        {
            this->log("'skipSplit' message was successfully sent.");
        }
        else
        {
            this->log("Error while sending message 'skipSplit' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".");
        }
    });
}

void LiveSplitToolkit::onUndoSplit()
{
    this->liveSplitClient.undoSplit([this](const int &errorCode, const std::string &errorMessage) {
        if (errorCode == 0)
        {
            this->log("'undoSplit' message was successfully sent.");
        }
        else
        {
            this->log("Error while sending message 'undoSplit' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".");
        }
    });
}

void LiveSplitToolkit::log(const std::string& message)
{
    this->plugin->cvarManager->log("LiveSplitToolkit: " + message);

}
//
// Created by Ian on 8/25/2020.
//

#include "LiveSplitToolkit.h"

LiveSplitToolkit::LiveSplitToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginToolkit(plugin), liveSplitClient(LiveSplitClient::getInstance(plugin))
{

}

std::string LiveSplitToolkit::title()
{
    return "LiveSplit Client";
}

void LiveSplitToolkit::onLoad()
{
    this->plugin->cvarManager->registerNotifier("srt_livesplit_connect", [this](const std::vector<std::string> &commands) {
        this->connect();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("srt_livesplit_startorsplit", [this](const std::vector<std::string> &commands) {
        this->startOrSplit();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
}

void LiveSplitToolkit::onUnload()
{

}

void LiveSplitToolkit::render()
{

}

void LiveSplitToolkit::connect()
{
    this->plugin->cvarManager->log("LiveSplitToolkit: Attempting to establish a connection with the LiveSplit Server...");
    this->plugin->gameWrapper->LogToChatbox("LiveSplitToolkit: Attempting to establish a connection with the LiveSplit Server...", "SPEEDRUNTOOLS");

    try
    {
        this->liveSplitClient.connect("localhost", "16834", [this](int errorCode, const std::string &errorMessage) {
            this->plugin->cvarManager->log("ec: " + std::to_string(errorCode) + ", em: " + errorMessage);
        });
    }
    catch (const std::exception &e)
    {
        this->plugin->cvarManager->log("LiveSplitToolkit: Failed to connect. " + std::string(e.what()));
        this->plugin->gameWrapper->LogToChatbox("LiveSplitToolkit: Failed to connect. " + std::string(e.what()), "SPEEDRUNTOOLS");

        this->plugin->cvarManager->log("LiveSplitToolkit: Make sure the LiveSplit Server is running and open on port 16834 " + std::string(e.what()));
        this->plugin->gameWrapper->LogToChatbox(
                "LiveSplitToolkit: Make sure the LiveSplit Server is running on localhost port 16834 " + std::string(e.what()), "SPEEDRUNTOOLS");
    }
}

void LiveSplitToolkit::startOrSplit()
{
    this->plugin->cvarManager->log("giving it a go");
    try
    {
        this->liveSplitClient.startOrSplit();
    }
    catch (const std::exception &e)
    {
        this->plugin->cvarManager->log("error start or split " + std::string(e.what()));
    }
}

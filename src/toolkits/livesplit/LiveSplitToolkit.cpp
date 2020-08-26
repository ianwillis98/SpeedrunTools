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

    try
    {
        this->liveSplitClient.connect("localhost", "16834", [this](const int &errorCode, const std::string &errorMessage) {
            this->plugin->gameWrapper->Execute([this, errorCode, errorMessage](GameWrapper *gw) {
                if (errorCode == 0)
                {
                    this->plugin->cvarManager->log("LiveSplitToolkit: Connection established with the LiveSplit Server.");
                }
                else
                {
                    this->plugin->cvarManager->log(
                            "LiveSplitToolkit: Error while connecting to the LiveSplit Server (" + std::to_string(errorCode) + ") \"" + errorMessage +
                            "\".");
                    this->plugin->cvarManager->log("LiveSplitToolkit: Make sure the LiveSplit Server is running and open on port 16834.");
                }
            });
        });
    }
    catch (const std::exception &e)
    {
        this->plugin->cvarManager->log("LiveSplitToolkit: There was an issue setting up the connection \"" + std::string(e.what()) + "\".");
    }
}

void LiveSplitToolkit::startOrSplit()
{
    try
    {
        this->liveSplitClient.startOrSplit();
    }
    catch (const std::exception &e)
    {
        this->plugin->cvarManager->log("error start or split " + std::string(e.what()));
    }
}

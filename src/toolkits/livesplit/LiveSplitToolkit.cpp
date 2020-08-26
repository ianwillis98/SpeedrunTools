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
    this->plugin->cvarManager->registerNotifier("st_ls_connect", [this](const std::vector<std::string> &commands) {
        this->connect();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("st_ls_startorsplit", [this](const std::vector<std::string> &commands) {
        this->startOrSplit();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("st_ls_start", [this](const std::vector<std::string> &commands) {
        this->start();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("st_ls_pause", [this](const std::vector<std::string> &commands) {
        this->pause();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("st_ls_resume", [this](const std::vector<std::string> &commands) {
        this->resume();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("st_ls_reset", [this](const std::vector<std::string> &commands) {
        this->reset();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("st_ls_split", [this](const std::vector<std::string> &commands) {
        this->split();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("st_ls_skipsplit", [this](const std::vector<std::string> &commands) {
        this->skipSplit();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("st_ls_undosplit", [this](const std::vector<std::string> &commands) {
        this->undoSplit();
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

void LiveSplitToolkit::startOrSplit()
{
    try
    {
        this->liveSplitClient.startOrSplit();
    }
    catch (const std::exception &e)
    {
        this->plugin->cvarManager->log("LiveSplitToolkit: Error while trying to send the command 'startorsplit' \"" + std::string(e.what()) + "\".");
    }
}

void LiveSplitToolkit::start()
{
    try
    {
        this->liveSplitClient.start();
    }
    catch (const std::exception &e)
    {
        this->plugin->cvarManager->log("LiveSplitToolkit: Error while trying to send the command 'start' \"" + std::string(e.what()) + "\".");
    }
}

void LiveSplitToolkit::pause()
{
    try
    {
        this->liveSplitClient.pause();
    }
    catch (const std::exception &e)
    {
        this->plugin->cvarManager->log("LiveSplitToolkit: Error while trying to send the command 'pause' \"" + std::string(e.what()) + "\".");
    }
}

void LiveSplitToolkit::resume()
{
    try
    {
        this->liveSplitClient.resume();
    }
    catch (const std::exception &e)
    {
        this->plugin->cvarManager->log("LiveSplitToolkit: Error while trying to send the command 'resume' \"" + std::string(e.what()) + "\".");
    }
}

void LiveSplitToolkit::reset()
{
    try
    {
        this->liveSplitClient.reset();
    }
    catch (const std::exception &e)
    {
        this->plugin->cvarManager->log("LiveSplitToolkit: Error while trying to send the command 'reset' \"" + std::string(e.what()) + "\".");
    }
}

void LiveSplitToolkit::split()
{
    try
    {
        this->liveSplitClient.split();
    }
    catch (const std::exception &e)
    {
        this->plugin->cvarManager->log("LiveSplitToolkit: Error while trying to send the command 'split' \"" + std::string(e.what()) + "\".");
    }
}

void LiveSplitToolkit::skipSplit()
{
    try
    {
        this->liveSplitClient.skipSplit();
    }
    catch (const std::exception &e)
    {
        this->plugin->cvarManager->log("LiveSplitToolkit: Error while trying to send the command 'skipSplit' \"" + std::string(e.what()) + "\".");
    }
}

void LiveSplitToolkit::undoSplit()
{
    try
    {
        this->liveSplitClient.undoSplit();
    }
    catch (const std::exception &e)
    {
        this->plugin->cvarManager->log("LiveSplitToolkit: Error while trying to send the command 'undoSplit' \"" + std::string(e.what()) + "\".");
    }
}

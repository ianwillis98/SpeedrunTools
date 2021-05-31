#include "LiveSplitModel.h"

LiveSplitModel &LiveSplitModel::getInstance(BakkesMod::Plugin::BakkesModPlugin *plugin)
{
    static LiveSplitModel instance(plugin);
    return instance;
}

LiveSplitModel::LiveSplitModel(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : client(LiveSplitClient::getInstance()),
          plugin(plugin),
          statusMessage("Waiting for a connection to the LiveSplit Server."),
          callback([this](bool success, const std::string &message) {
              this->handleResultCallback(success, message);
          })
{

}

void LiveSplitModel::connect()
{
    this->statusMessage = "Attempting to establish a connection with the LiveSplit Server...";
    this->log(this->statusMessage);
    this->client.connect("localhost", "16834", callback);
}

void LiveSplitModel::disconnect()
{
    this->client.disconnect(callback);
}

bool LiveSplitModel::isConnected() const
{
    return this->client.isConnected();
}

bool LiveSplitModel::isConnecting() const
{
    return this->client.isConnecting();
}

void LiveSplitModel::startOrSplit()
{
    this->client.startOrSplit(callback);
}

void LiveSplitModel::start()
{
    this->client.start(callback);
}

void LiveSplitModel::pause()
{
    this->client.pause(callback);
}

void LiveSplitModel::resume()
{
    this->client.resume(callback);
}

void LiveSplitModel::reset()
{
    this->client.reset(callback);
}

void LiveSplitModel::split()
{
    this->client.split(callback);
}

void LiveSplitModel::skipSplit()
{
    this->client.skipSplit(callback);
}

void LiveSplitModel::undoSplit()
{
    this->client.undoSplit(callback);
}

std::string LiveSplitModel::getStatusMessage()
{
    return this->statusMessage;
}

void LiveSplitModel::handleResultCallback(bool success, const std::string &message)
{
    this->statusMessage = message;
    this->log(this->statusMessage);
}

void LiveSplitModel::log(const std::string &message)
{
    std::string m = "LiveSplit: " + message;

    this->plugin->cvarManager->log(m);
//    if (this->shouldLogToChatbox) this->plugin->gameWrapper->LogToChatbox(m, "SPEEDRUNTOOLS");
}

#include "LiveSplitModel.h"

LiveSplitModel::LiveSplitModel(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : plugin(plugin),
          client(LiveSplitClient::getInstance())
{

}

void LiveSplitModel::connect()
{
    this->status = "Attempting to establish a connection with the LiveSplit Server...";
    this->logStatus();
    this->client.connect("localhost", "16834", [this](const int &errorCode, const std::string &errorMessage) {
        this->status = (errorCode == 0) ? "Connection established with the LiveSplit Server." :
                       "Error while connecting to the LiveSplit Server (" + std::to_string(errorCode) + ") \"" + errorMessage + "\"." +
                       "\nMake sure the LiveSplit Server is running and open on port 16834.";
        this->logStatus();
    });
}

void LiveSplitModel::disconnect()
{
    this->client.disconnect([this](const int &errorCode, const std::string &errorMessage) {
        this->status = (errorCode == 0) ? "Disconnected from the LiveSplit Server." :
                       "Error while disconnecting from the LiveSplit Server (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->logStatus();
    });
}

void LiveSplitModel::startOrSplit()
{
    this->client.startOrSplit([this](const int &errorCode, const std::string &errorMessage) {
        this->status = (errorCode == 0) ? "'startOrSplit' message was successfully sent." :
                       "Error while sending message 'startOrSplit' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->logStatus();
    });
}

void LiveSplitModel::start()
{
    this->client.start([this](const int &errorCode, const std::string &errorMessage) {
        this->status = (errorCode == 0) ? "'startTimer' message was successfully sent." :
                       "Error while sending message 'startTimer' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->logStatus();
    });
}

void LiveSplitModel::stop()
{
    this->client.pause([this](const int &errorCode, const std::string &errorMessage) {
        this->status = (errorCode == 0) ? "'pause' message was successfully sent." :
                       "Error while sending message 'pause' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->logStatus();
    });
}

void LiveSplitModel::pause()
{
    this->client.pause([this](const int &errorCode, const std::string &errorMessage) {
        this->status = (errorCode == 0) ? "'pause' message was successfully sent." :
                       "Error while sending message 'pause' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->logStatus();
    });
}

void LiveSplitModel::resume()
{
    this->client.resume([this](const int &errorCode, const std::string &errorMessage) {
        this->status = (errorCode == 0) ? "'resume' message was successfully sent." :
                       "Error while sending message 'resume' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->logStatus();
    });
}

void LiveSplitModel::split()
{
    this->client.split([this](const int &errorCode, const std::string &errorMessage) {
        this->status = (errorCode == 0) ? "'splitTimer' message was successfully sent." :
                       "Error while sending message 'splitTimer' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->logStatus();
    });
}
void LiveSplitModel::skipSplit()
{
    this->client.skipSplit([this](const int &errorCode, const std::string &errorMessage) {
        this->status = (errorCode == 0) ? "'skipSplit' message was successfully sent." :
                       "Error while sending message 'skipSplit' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->logStatus();
    });
}
void LiveSplitModel::undoSplit()
{
    this->client.undoSplit([this](const int &errorCode, const std::string &errorMessage) {
        this->status = (errorCode == 0) ? "'undoSplit' message was successfully sent." :
                       "Error while sending message 'undoSplit' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->logStatus();
    });
}

bool LiveSplitModel::isNotConnected()
{
    return this->client.getConnectionState() == ConnectionState::NotConnected;
}

bool LiveSplitModel::isConnecting()
{
    return this->client.getConnectionState() == ConnectionState::Connecting;
}

bool LiveSplitModel::isConnected()
{
    return this->client.getConnectionState() == ConnectionState::Connected;
}

std::string LiveSplitModel::getStatusMessage()
{
    return this->status;
}

void LiveSplitModel::logStatus()
{
    this->plugin->cvarManager->log("LiveSplit: " + this->status);
}

#include "LiveSplitModel.h"

LiveSplitModel::LiveSplitModel(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginModel(plugin),
          client(LiveSplitClient::getInstance()),
          status()
{

}

void LiveSplitModel::connect(const ResultsCallback &callback)
{
    this->status = "Attempting to establish a connection with the LiveSplit Server...";
    this->client.connect("localhost", "16834", [this, callback](const int &errorCode, const std::string &errorMessage) {
        this->status = (errorCode == 0) ? "Connection established with the LiveSplit Server." :
                       "Error while connecting to the LiveSplit Server (" + std::to_string(errorCode) + ") \"" + errorMessage + "\"." +
                       "\nMake sure the LiveSplit Server is running and open on port 16834.";
        callback(errorCode == 0, this->status);
    });
}

void LiveSplitModel::disconnect(const ResultsCallback &callback)
{
    this->client.disconnect([this, callback](const int &errorCode, const std::string &errorMessage) {
        this->status = (errorCode == 0) ? "Disconnected from the LiveSplit Server." :
                       "Error while disconnecting from the LiveSplit Server (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        callback(errorCode == 0, this->status);
    });
}

void LiveSplitModel::startOrSplit(const ResultsCallback &callback)
{
    this->client.startOrSplit([this, callback](const int &errorCode, const std::string &errorMessage) {
        this->status = (errorCode == 0) ? "'startOrSplit' message was successfully sent." :
                       "Error while sending message 'startOrSplit' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        callback(errorCode == 0, this->status);
    });
}

void LiveSplitModel::start(const ResultsCallback &callback)
{
    this->client.start([this, callback](const int &errorCode, const std::string &errorMessage) {
        this->status = (errorCode == 0) ? "'startTimer' message was successfully sent." :
                       "Error while sending message 'startTimer' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        callback(errorCode == 0, this->status);
    });
}

void LiveSplitModel::stop(const ResultsCallback &callback)
{
    this->client.pause([this, callback](const int &errorCode, const std::string &errorMessage) {
        this->status = (errorCode == 0) ? "'pause' message was successfully sent." :
                       "Error while sending message 'pause' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        callback(errorCode == 0, this->status);
    });
}

void LiveSplitModel::pause(const ResultsCallback &callback)
{
    this->client.pause([this, callback](const int &errorCode, const std::string &errorMessage) {
        this->status = (errorCode == 0) ? "'pause' message was successfully sent." :
                       "Error while sending message 'pause' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        callback(errorCode == 0, this->status);
    });
}

void LiveSplitModel::resume(const ResultsCallback &callback)
{
    this->client.resume([this, callback](const int &errorCode, const std::string &errorMessage) {
        this->status = (errorCode == 0) ? "'resume' message was successfully sent." :
                       "Error while sending message 'resume' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        callback(errorCode == 0, this->status);
    });
}

void LiveSplitModel::split(const ResultsCallback &callback)
{
    this->client.split([this, callback](const int &errorCode, const std::string &errorMessage) {
        this->status = (errorCode == 0) ? "'splitTimer' message was successfully sent." :
                       "Error while sending message 'splitTimer' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        callback(errorCode == 0, this->status);
    });
}
void LiveSplitModel::skipSplit(const ResultsCallback &callback)
{
    this->client.skipSplit([this, callback](const int &errorCode, const std::string &errorMessage) {
        this->status = (errorCode == 0) ? "'skipSplit' message was successfully sent." :
                       "Error while sending message 'skipSplit' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        callback(errorCode == 0, this->status);
    });
}
void LiveSplitModel::undoSplit(const ResultsCallback &callback)
{
    this->client.undoSplit([this, callback](const int &errorCode, const std::string &errorMessage) {
        this->status = (errorCode == 0) ? "'undoSplit' message was successfully sent." :
                       "Error while sending message 'undoSplit' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        callback(errorCode == 0, this->status);
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

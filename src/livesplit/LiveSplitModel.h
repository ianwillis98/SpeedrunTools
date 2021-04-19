#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <bakkesmod/plugin/bakkesmodplugin.h>
#include "../services/LiveSplitClient.h"
#include "../PluginModel.h"

using ResultsCallback = std::function<void(bool success, std::string status)>;

class LiveSplitModel : public PluginModel
{

private:
    LiveSplitClient &client;
    std::string status;

public:
    explicit LiveSplitModel(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void connect(const ResultsCallback &callback);
    void disconnect(const ResultsCallback &callback);

    void startOrSplit(const ResultsCallback &callback);

    void start(const ResultsCallback &callback);
    void stop(const ResultsCallback &callback);

    void pause(const ResultsCallback &callback);
    void resume(const ResultsCallback &callback);

    void split(const ResultsCallback &callback);
    void skipSplit(const ResultsCallback &callback);
    void undoSplit(const ResultsCallback &callback);

    bool isNotConnected();
    bool isConnecting();
    bool isConnected();

    std::string getStatusMessage();
};

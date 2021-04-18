#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <bakkesmod/plugin/bakkesmodplugin.h>
#include "../../services/LiveSplitClient.h"

class LiveSplitModel
{
private:
    BakkesMod::Plugin::BakkesModPlugin *plugin;
    LiveSplitClient &client;
    std::string status;

public:
    explicit LiveSplitModel(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void connect();
    void disconnect();

    void startOrSplit();

    void start();
    void stop();

    void pause();
    void resume();

    void split();
    void skipSplit();
    void undoSplit();

    bool isNotConnected();
    bool isConnecting();
    bool isConnected();

    std::string getStatusMessage();

private:
    void logStatus();
};

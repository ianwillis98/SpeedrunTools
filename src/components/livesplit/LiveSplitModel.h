#pragma once

#include "../../services/LiveSplitClient.h"

class LiveSplitModel
{
public:
    using ResultCallback = std::function<void(bool success, std::string status)>;

private:
    BakkesMod::Plugin::BakkesModPlugin *plugin;

    LiveSplitClient &client;
    std::string statusMessage;
    ResultCallback callback;

    explicit LiveSplitModel(BakkesMod::Plugin::BakkesModPlugin *plugin);

public:
    static LiveSplitModel &getInstance(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void connect();
    void disconnect();
    bool isConnected() const;
    bool isConnecting() const;

    void startOrSplit();

    void start();
    void pause();
    void resume();
    void reset();

    void split();
    void skipSplit();
    void undoSplit();

    std::string getStatusMessage();

private:
    void handleResultCallback(bool success, const std::string &message);
    void log(const std::string &message);
};

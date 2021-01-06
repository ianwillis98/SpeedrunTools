#pragma once

#include "../PluginComponentBase.h"
#include "../../services/LiveSplitClient.h"
#include "autosplitters/AutoSplitter.h"

class LiveSplitRemoteComponent : public PluginComponentBase
{
private:
    LiveSplitClient &liveSplitClient;
    std::string feedbackMessage;

public:
    explicit LiveSplitRemoteComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onLoad() override;
    void render() override;

private:
    void connectAsync();
    void disconnect();

    void startOrSplit();

    void start();
    void pause();
    void resume();
    void reset();

    void split();
    void skipSplit();
    void undoSplit();

    void log(const std::string &message);

    std::string getConnectionStatusAsString();
};

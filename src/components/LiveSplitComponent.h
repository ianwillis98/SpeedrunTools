#pragma once

#include "../PluginComponent.h"
#include "../services/LiveSplitClient.h"
#include "autosplitters/AutoSplitterManager.h"

class LiveSplitComponent : public PluginComponent
{
private:
    LiveSplitClient &liveSplitClient;
    std::string feedbackMessage;

    AutoSplitterManager &autoSplitterManager;
    std::string currentMap;
    bool isCurrentMapSupported;
    bool isAutoSplitterRunning;

public:
    explicit LiveSplitComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    std::string title() override;
    void onLoad() override;
    void render() override;
    void onEvent(std::string eventName, bool post, void *params) override;

private:
    void renderLiveSplitClient();
    void renderAutoSplitter();

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
};

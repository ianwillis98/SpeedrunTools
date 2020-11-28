#pragma once

#include "../PluginComponent.h"
#include "../services/LiveSplitClient.h"

class LiveSplitComponent : public PluginComponent
{
private:
    LiveSplitClient &liveSplitClient;
    std::string feedbackMessage;

public:
    explicit LiveSplitComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    std::string title() override;
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
};

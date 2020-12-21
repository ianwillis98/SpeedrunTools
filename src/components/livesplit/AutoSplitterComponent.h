#pragma once

#include "../PluginComponentBase.h"
#include "../../services/LiveSplitClient.h"
#include "AutoSplitter.h"

class AutoSplitterComponent : public PluginComponentBase
{
private:
    LiveSplitClient &liveSplitClient;
    std::string feedbackMessage;
    std::unique_ptr<AutoSplitter> autoSplitter;

public:
    explicit AutoSplitterComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onLoad() override;
    void render() override;
    void onEvent(const std::string &eventName, bool post, void *params) override;

private:
    void start();
    void split();
    void reset();

    void log(const std::string &message);
};

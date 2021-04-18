#pragma once

#include "../AutoSplitterComponent.h"

class TutorialBasicAutoSplitterComponent : public PluginComponentBase
{
private:
    LiveSplitClient &liveSplitClient;

    bool isEnabled;
    bool isAutoStartEnabled;
    bool isAutoSplitEnabled;
    bool isAutoResetEnabled;

    bool isInTutorial;
    int segment;

public:
    explicit TutorialBasicAutoSplitterComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onLoad() override;
    void render() override;
    void onEvent(const std::string &eventName, bool post, void *params) override;

private:
    void start();
    void split();
    void reset();

    void log(const std::string &message);

    std::string getDebugText() const;
};

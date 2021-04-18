#pragma once

#include "../PluginComponentBase.h"
#include "../../services/LiveSplitClient.h"

class AutoSplitterComponent : public PluginComponentBase
{
protected:
    LiveSplitClient &liveSplitClient;
    std::string logPrefix;

    bool isEnabled;

    bool supportsAutoStart;
    bool isAutoStartEnabled;

    bool supportsAutoSplit;
    bool isAutoSplitEnabled;

    bool supportsAutoReset;
    bool isAutoResetEnabled;


public:
    explicit AutoSplitterComponent(BakkesMod::Plugin::BakkesModPlugin *plugin, std::string logPrefix);

    void render() final;
    void onEvent(const std::string &eventName, bool post, void *params) final;

protected:
    virtual void update(const std::string &eventName, bool post, void *params) = 0;
    virtual std::string getStartDescription();
    virtual std::string getSplitDescription();
    virtual std::string getResetDescription();
    virtual std::string getDebugText();

    void startTimer();
    void splitTimer();
    void resetTimer();

    void log(const std::string &message);
};

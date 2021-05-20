#pragma once

#include <bakkesmod/wrappers/kismet/SequenceWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceVariableWrapper.h>

#include "../PluginComponentBase.h"
#include "../livesplit/LiveSplitModel.h"

class AutoSplitterComponent : public PluginComponentBase
{
protected:
    LiveSplitModel &liveSplitModel;

    bool isEnabled;

    bool supportsAutoStart;
    bool isAutoStartEnabled;

    bool supportsAutoSplit;
    bool isAutoSplitEnabled;

    bool supportsAutoReset;
    bool isAutoResetEnabled;

public:
    explicit AutoSplitterComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void render() final;
    void onEvent(const std::string &eventName, bool post, void *params) final;

    void startTimer();
    void splitTimer();
    void resetTimer();

private:
    void renderConnectView();
    std::string getDebugTextPrefix() const;

protected:
    virtual void onEnable();
    virtual void update(const std::string &eventName, bool post, void *params) = 0;
    virtual std::string getStartDescription();
    virtual std::string getSplitDescription();
    virtual std::string getResetDescription();
    virtual std::string getDebugText();
};

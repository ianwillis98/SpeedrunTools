#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "../../PluginComponentBase.h"
#include "../../../services/LiveSplitClient.h"
#include "../../livesplit/LiveSplitModel.h"

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

private:
    void renderConnectView();
    std::string getDebugTextPrefix() const;

protected:
    void startTimer();
    void splitTimer();
    void resetTimer();

    virtual void update(const std::string &eventName, bool post, void *params) = 0;
    virtual std::string getStartDescription();
    virtual std::string getSplitDescription();
    virtual std::string getResetDescription();
    virtual std::string getDebugText();
};

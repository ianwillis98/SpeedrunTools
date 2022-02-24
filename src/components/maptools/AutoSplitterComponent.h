#pragma once

#include "../PluginComponentBase.h"
#include "../livesplit/LiveSplitModel.h"
#include "../kismet/KismetModel.h"

class AutoSplitterComponent : public PluginComponentBase
{
protected:
    LiveSplitModel &liveSplitModel;
    KismetModel &kismetModel;

    bool isEnabled;
    bool isAutoStartEnabled;
    bool isAutoSplitEnabled;
    bool isAutoResetEnabled;

    int segment;

public:
    explicit AutoSplitterComponent(NetcodePlugin *plugin);

    void onEvent(const std::string &eventName, bool post, void *params) final;
    void render() final;

    virtual void onMapReset();
    void disable();

private:
    void renderConnectView();
    std::string getDebugTextPrefix() const;

protected:
    virtual void onEnable();
    virtual void update(const std::string &eventName, bool post, void *params) = 0;

    void start(bool netcode = false);
    void split(bool netcode = false);
    void reset(bool netcode = false);

    virtual std::string getStartDescription();
    virtual std::string getSplitDescription();
    virtual std::string getResetDescription();
    virtual std::string getDebugText();
};

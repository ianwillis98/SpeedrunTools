#pragma once

#include "PluginToolkitBase.h"
#include "../components/savestates/SaveStateComponent.h"
#include "../components/savestates/RewindComponent.h"

class SaveStatesToolkit : public PluginToolkitBase
{
private:
    SaveStateComponent saveStateComponent;
    RewindComponent rewindComponent;

public:
    explicit SaveStatesToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin);

    std::string title() override;
    void onLoad() override;
    void render() override;
    void onEvent(const std::string &eventName, bool post, void *params) override;
};

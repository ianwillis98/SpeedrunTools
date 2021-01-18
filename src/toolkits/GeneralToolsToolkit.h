#pragma once

#include "PluginToolkitBase.h"
#include "../components/generaltools/GeneralToolsComponent.h"

class GeneralToolsToolkit : public PluginToolkitBase
{
private:
    GeneralToolsComponent generalToolsComponent;

public:
    explicit GeneralToolsToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin);

    std::string title() override;
    void onLoad() override;
    void render() override;
    void onEvent(const std::string &eventName, bool post, void *params) override;
};

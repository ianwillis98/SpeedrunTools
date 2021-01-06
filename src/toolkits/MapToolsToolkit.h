#pragma once

#include "PluginToolkitBase.h"
#include "../components/maptools/MapToolsComponent.h"

class MapToolsToolkit : public PluginToolkitBase
{
private:
    MapToolsComponent mapToolsComponent;

public:
    explicit MapToolsToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin);

    std::string title() override;
    void onLoad() override;
    void render() override;
    void onEvent(const std::string &eventName, bool post, void *params) override;
};

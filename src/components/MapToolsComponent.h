#pragma once

#include "../PluginComponent.h"

class MapToolsComponent : public PluginComponent
{
private:
    std::string currentMapName;

public:
    explicit MapToolsComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    std::string title() override;
    void onLoad() override;
    void render() override;
    void onEvent(std::string eventName, bool post, void *params) override;

};

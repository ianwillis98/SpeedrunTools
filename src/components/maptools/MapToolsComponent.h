#pragma once

#include "../PluginComponentBase.h"
#include "MapTools.h"

class SupportedMap
{
public:
    std::string mapName;
    std::unique_ptr<MapTools> mapTools;

    SupportedMap(std::string mapName, std::unique_ptr<MapTools> mapTools) : mapName(std::move(mapName)), mapTools(std::move(mapTools))
    {}
};

class MapToolsComponent : public PluginComponentBase
{
private:
    std::vector<SupportedMap> supportedMaps;

public:
    explicit MapToolsComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onLoad() override;
    void render() override;
    void onEvent(const std::string &eventName, bool post, void *params) override;
};

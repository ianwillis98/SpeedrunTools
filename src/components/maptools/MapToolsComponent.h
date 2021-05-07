#pragma once

#include "../PluginComponentBase.h"

class MapToolsComponent : public PluginComponentBase
{
private:
    std::vector<std::pair<std::string, std::unique_ptr<PluginComponent>>> supportedMaps;
    int comboIndex;

public:
    explicit MapToolsComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void render() override;
    void onEvent(const std::string &eventName, bool post, void *params) override;
};

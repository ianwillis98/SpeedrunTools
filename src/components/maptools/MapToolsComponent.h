#pragma once

#include "../PluginComponentBase.h"

class MapToolsComponent : public PluginComponentBase
{
public:
    explicit MapToolsComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onLoad() override;
    void render() override;
    void onEvent(const std::string &eventName, bool post, void *params);
};

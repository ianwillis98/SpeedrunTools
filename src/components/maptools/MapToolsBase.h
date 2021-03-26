#pragma once

#include "MapTools.h"

class MapToolsBase : public MapTools
{
protected:
    BakkesMod::Plugin::BakkesModPlugin *plugin;

public:
    explicit MapToolsBase(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onLoad() override;
    void onUnload() override;
    void render() override;
    void onEvent(const std::string &eventName, bool post, void *params) override;
};


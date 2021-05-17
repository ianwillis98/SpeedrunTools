#pragma once

#include "../PluginComponentBase.h"
#include "MapToolsComponent.h"

class MapToolsSelectorComponent : public PluginComponentBase
{
private:
    std::vector<std::unique_ptr<MapToolsComponent>> maps;
    int selectedMapIndex;

public:
    explicit MapToolsSelectorComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void render() override;
    void renderCanvas(CanvasWrapper &canvasWrapper) override;
    void onEvent(const std::string &eventName, bool post, void *params) override;
};

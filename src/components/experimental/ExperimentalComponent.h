#pragma once

#include "../PluginComponentBase.h"

class ExperimentalComponent : public PluginComponentBase
{
public:
    explicit ExperimentalComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void render() override;
    void renderCanvas(CanvasWrapper &canvasWrapper);
    void onEvent(const std::string &eventName, bool post, void *params) override;
};

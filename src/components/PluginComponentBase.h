#pragma once

#include "../PluginComponent.h"

class PluginComponentBase : public PluginComponent
{
protected:
    BakkesMod::Plugin::BakkesModPlugin *plugin;

public:
    explicit PluginComponentBase(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onEvent(const std::string &eventName, bool post, void *params) override;

    void render() override;
    void renderCanvas(CanvasWrapper &canvasWrapper) override;
};

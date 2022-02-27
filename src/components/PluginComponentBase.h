#pragma once

#include "../PluginComponent.h"
#include "../NetcodePlugin.h"

class PluginComponentBase : public PluginComponent
{
protected:
    NetcodePlugin *plugin;

public:
    explicit PluginComponentBase(NetcodePlugin* plugin);

    void onEvent(const std::string &eventName, bool post, void *params) override;

    void render() override;
    void renderCanvas(CanvasWrapper &canvasWrapper) override;
};

#pragma once

#include "../PluginComponentBase.h"
#include "TestVar.h"

class ExperimentalComponent : public PluginComponentBase
{
public:
    std::vector<TestVar> vars;

    explicit ExperimentalComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onEvent(const std::string &eventName, bool post, void *params) override;

    void render() override;
    void renderCanvas(CanvasWrapper &canvasWrapper) override;

    void assign();
};

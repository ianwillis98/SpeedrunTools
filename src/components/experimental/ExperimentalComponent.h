#pragma once

#include "../PluginComponentBase.h"
#include "../../models/collision/Rect3d.h"

class ExperimentalComponent : public PluginComponentBase
{
private:
    bool fly;
    bool isBoostPressed;

    bool lockToCar;

    Vector center;
    Vector size;
    Rotator rotation;
    Rect3d rect;

public:
    explicit ExperimentalComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void render() override;
    void renderCanvas(CanvasWrapper &canvasWrapper) override;
    void onEvent(const std::string &eventName, bool post, void *params) override;
};

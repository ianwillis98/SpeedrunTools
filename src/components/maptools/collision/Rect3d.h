#pragma once

#include <renderingtools/objects/Rect3d.h>

class Rect3d
{
private:
    Vector center;
    Vector size;
    Rotator rotation;
    RT::Rect3d rect;

public:
    Rect3d(Vector center, Vector size, Rotator rotation, BakkesMod::Plugin::BakkesModPlugin *plugin);

    void renderCanvas(CanvasWrapper &canvasWrapper, CameraWrapper &cameraWrapper);

    bool contains(Vector point);
};

#pragma once

#include <renderingtools/objects/RectangularPrism.h>

class Aabb
{
private:
    Vector corner;
    Vector size;

    RT::RectangularPrism rect;

public:
    Aabb(Vector corner, Vector size);

    void render();
    void renderCanvas(CanvasWrapper &canvasWrapper, CameraWrapper &cameraWrapper);

    bool intersects(Vector point);
};

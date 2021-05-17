#include "Rect3d.h"

Rect3d::Rect3d(Vector center, Vector size, Rotator rotation, BakkesMod::Plugin::BakkesModPlugin *plugin)
        : center(center), size(size), rotation(rotation), rect(center, size, rotation, 3, plugin)
{

}

void Rect3d::renderCanvas(CanvasWrapper &canvasWrapper, CameraWrapper &cameraWrapper)
{
    RT::Frustum frustum(canvasWrapper, cameraWrapper);
    this->rect.Draw(canvasWrapper, frustum);
}

bool Rect3d::contains(Vector point)
{
    float halfWidth = size.X / 2;
    float halfHeight = size.Y / 2;
    float halfDepth = size.Z / 2;
    Vector a(center.X - halfWidth, center.Y - halfHeight, center.Z - halfDepth);
    Vector b(center.X + halfWidth, center.Y - halfHeight, center.Z - halfDepth);
    Vector c(center.X - halfWidth, center.Y + halfHeight, center.Z - halfDepth);
    Vector d(center.X - halfWidth, center.Y - halfHeight, center.Z + halfDepth);

    float xLength = (b - a).magnitude();
    float yLength = (c - a).magnitude();
    float zLength = (d - a).magnitude();

    return false;
}

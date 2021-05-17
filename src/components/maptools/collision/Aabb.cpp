#include <renderingtools/objects/Frustum.h>
#include "Aabb.h"

Aabb::Aabb(Vector corner, Vector size)
        : corner(corner), size(size), rect(corner, size, 1)
{

}

void Aabb::render()
{

}

void Aabb::renderCanvas(CanvasWrapper &canvasWrapper, CameraWrapper &cameraWrapper)
{
    RT::Frustum frustum(canvasWrapper, cameraWrapper);
    rect.Draw(canvasWrapper, frustum);
}

bool Aabb::intersects(Vector point)
{
    float xMin = std::fminf(corner.X, corner.X + size.X);
    float xMax = std::fmaxf(corner.X, corner.X + size.X);
    float yMin = std::fminf(corner.Y, corner.Y + size.Y);
    float yMax = std::fmaxf(corner.Y, corner.Y + size.Y);
    float zMin = std::fminf(corner.Z, corner.Z + size.Z);
    float zMax = std::fmaxf(corner.Z, corner.Z + size.Z);

    return (xMin <= point.X) && (point.X <= xMax)
           && (yMin <= point.Y) && (point.Y <= yMax)
           && (zMin <= point.Z) && (point.Z <= zMax);
}

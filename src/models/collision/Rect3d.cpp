#include "Rect3d.h"

Rect3d::Rect3d(Vector center, Vector size, Rotator rotation)
        : center(center), size(size), rotation(rotation), rtrect(center, size, rotation)
{

}

void Rect3d::render()
{
    float centerArray[3] = {this->center.X, this->center.Y, this->center.Z};
    if (ImGui::InputFloat3("center (x,y,z)", centerArray, 2, ImGuiInputTextFlags_EnterReturnsTrue))
    {
        this->center = Vector(centerArray[0], centerArray[1], centerArray[2]);
        this->rtrect = RT::Rect3d(this->center, this->size, this->rotation);
    }

    float sizeArray[3] = {this->size.X, this->size.Y, this->size.Z};
    if (ImGui::InputFloat3("size (x,y,z)", sizeArray, 2, ImGuiInputTextFlags_EnterReturnsTrue))
    {
        this->size = Vector(sizeArray[0], sizeArray[1], sizeArray[2]);
        this->rtrect = RT::Rect3d(this->center, this->size, this->rotation);
    }

    int rotationArray[3] = {this->rotation.Pitch, this->rotation.Yaw, this->rotation.Roll};
    if (ImGui::InputInt3("rotation (pitch,yaw,roll)", rotationArray, ImGuiInputTextFlags_EnterReturnsTrue))
    {
        this->rotation = Rotator(rotationArray[0], rotationArray[1], rotationArray[2]);
        this->rtrect = RT::Rect3d(this->center, this->size, this->rotation);
    }
}

void Rect3d::renderCanvas(CanvasWrapper &canvasWrapper, CameraWrapper &cameraWrapper)
{
    RT::Frustum frustum(canvasWrapper, cameraWrapper);
    this->rtrect.Draw(canvasWrapper, frustum);
}

bool Rect3d::contains(Vector point)
{
    Quat quat = RotatorToQuat(Rotator() - rotation);
    point = point - center;
    point = RotateVectorWithQuat(point, quat) + center;

    float halfWidth = size.X / 2;
    float halfHeight = size.Y / 2;
    float halfDepth = size.Z / 2;

    float xMin = center.X - halfWidth;
    float xMax = center.X + halfWidth;
    float yMin = center.Y - halfHeight;
    float yMax = center.Y + halfHeight;
    float zMin = center.Z - halfDepth;
    float zMax = center.Z + halfDepth;

    return (xMin <= point.X) && (point.X <= xMax)
           && (yMin <= point.Y) && (point.Y <= yMax)
           && (zMin <= point.Z) && (point.Z <= zMax);
}

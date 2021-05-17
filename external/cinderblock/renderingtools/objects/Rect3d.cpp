#include <bakkesmod/plugin/bakkesmodplugin.h>
#include "Rect3d.h"

RT::Rect3d::Rect3d(Vector center, Vector size, Rotator rotation, float thickness, BakkesMod::Plugin::BakkesModPlugin *plugin)
{
    Quat quat = RotatorToQuat(rotation);

    Vector zero(0, 0, 0);
    Vector halfSize = size / 2;
    Vector width = Vector(size.X, 0, 0);
    Vector height = Vector(0, size.Y, 0);
    Vector depth = Vector(0, 0, size.Z);

    Vector point1 = zero - halfSize;
    Vector point2 = point1 + width;
    Vector point3 = point1 + height;
    Vector point4 = point1 + depth;
    Vector point5 = point1 + width + height;
    Vector point6 = point1 + width + depth;
    Vector point7 = point1 + height + depth;
    Vector point8 = point1 + size;

    point1 = RotateVectorWithQuat(point1, quat) + center;
    point2 = RotateVectorWithQuat(point2, quat) + center;
    point3 = RotateVectorWithQuat(point3, quat) + center;
    point4 = RotateVectorWithQuat(point4, quat) + center;
    point5 = RotateVectorWithQuat(point5, quat) + center;
    point6 = RotateVectorWithQuat(point6, quat) + center;
    point7 = RotateVectorWithQuat(point7, quat) + center;
    point8 = RotateVectorWithQuat(point8, quat) + center;

    this->line1 = RT::Line(point1, point2, thickness);
    this->line2 = RT::Line(point1, point3, thickness);
    this->line3 = RT::Line(point1, point4, thickness);

    this->line4 = RT::Line(point2, point5, thickness);
    this->line5 = RT::Line(point2, point6, thickness);

    this->line6 = RT::Line(point4, point6, thickness);
    this->line7 = RT::Line(point4, point7, thickness);

    this->line8 = RT::Line(point3, point5, thickness);
    this->line9 = RT::Line(point3, point7, thickness);

    this->line10 = RT::Line(point8, point5, thickness);
    this->line11 = RT::Line(point8, point6, thickness);
    this->line12 = RT::Line(point8, point7, thickness);
}

void RT::Rect3d::Draw(CanvasWrapper &canvas, RT::Frustum &frustum)
{
    this->line1.DrawWithinFrustum(canvas, frustum);
    this->line2.DrawWithinFrustum(canvas, frustum);
    this->line3.DrawWithinFrustum(canvas, frustum);
    this->line4.DrawWithinFrustum(canvas, frustum);
    this->line5.DrawWithinFrustum(canvas, frustum);
    this->line6.DrawWithinFrustum(canvas, frustum);
    this->line7.DrawWithinFrustum(canvas, frustum);
    this->line8.DrawWithinFrustum(canvas, frustum);
    this->line9.DrawWithinFrustum(canvas, frustum);
    this->line10.DrawWithinFrustum(canvas, frustum);
    this->line11.DrawWithinFrustum(canvas, frustum);
    this->line12.DrawWithinFrustum(canvas, frustum);
}

void RT::Rect3d::log(std::string name, BakkesMod::Plugin::BakkesModPlugin *plugin, Vector vector)
{
    plugin->cvarManager->log(name + ": x=" + std::to_string(vector.X) + ",y=" + std::to_string(vector.Y) + ",z=" + std::to_string(vector.Z));
}

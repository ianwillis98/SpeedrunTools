#include "RectangularPrism.h"

RT::RectangularPrism::RectangularPrism(Vector point1, Vector point2, Vector xDiff, Vector yDiff, Vector zDiff, float thickness)
        : line1(point1, point1 + xDiff, thickness),
          line2(point1, point1 + yDiff, thickness),
          line3(point1, point1 + zDiff, thickness),
          line4(point1 + xDiff, point1 + xDiff + yDiff, thickness),
          line5(point1 + xDiff, point1 + xDiff + zDiff, thickness),
          line6(point1 + yDiff, point1 + yDiff + xDiff, thickness),
          line7(point1 + yDiff, point1 + yDiff + zDiff, thickness),
          line8(point1 + zDiff, point1 + zDiff + xDiff, thickness),
          line9(point1 + zDiff, point1 + zDiff + yDiff, thickness),
          line10(point2, point2 - xDiff, thickness),
          line11(point2, point2 - yDiff, thickness),
          line12(point2, point2 - zDiff, thickness)
{
    Rotator rotator(0, 9000, 0);

    Quat quat = RotatorToQuat(rotator);

    Vector center(point1 + ((point2 - point1) / 2));
    Vector r1(point1 - center);
    Vector r2(point1 - center + xDiff);
    r1 = RotateVectorWithQuat(r1, quat) + center;
    r2 = RotateVectorWithQuat(r2, quat) + center;

    this->line1 = RT::Line(r1, r2, thickness);
}

RT::RectangularPrism::RectangularPrism(Vector point1, Vector point2, float thickness)
        : RectangularPrism(point1, point2, Vector(point2.X - point1.X, 0, 0), Vector(0, point2.Y - point1.Y, 0), Vector(0, 0, point2.Z - point1.Z),
                           thickness)
{

}

void RT::RectangularPrism::Draw(CanvasWrapper canvas, RT::Frustum &frustum)
{
    line1.DrawWithinFrustum(canvas, frustum);
    line2.DrawWithinFrustum(canvas, frustum);
    line3.DrawWithinFrustum(canvas, frustum);
    line4.DrawWithinFrustum(canvas, frustum);
    line5.DrawWithinFrustum(canvas, frustum);
    line6.DrawWithinFrustum(canvas, frustum);
    line7.DrawWithinFrustum(canvas, frustum);
    line8.DrawWithinFrustum(canvas, frustum);
    line9.DrawWithinFrustum(canvas, frustum);
    line10.DrawWithinFrustum(canvas, frustum);
    line11.DrawWithinFrustum(canvas, frustum);
    line12.DrawWithinFrustum(canvas, frustum);
}

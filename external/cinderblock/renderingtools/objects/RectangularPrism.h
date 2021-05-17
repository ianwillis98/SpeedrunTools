#pragma once

#include <bakkesmod/wrappers/wrapperstructs.h>
#include <bakkesmod/wrappers/canvaswrapper.h>
#include "Frustum.h"
#include "Line.h"

namespace RT
{
    class RectangularPrism
    {
    private:
        RT::Line line1;
        RT::Line line2;
        RT::Line line3;
        RT::Line line4;
        RT::Line line5;
        RT::Line line6;
        RT::Line line7;
        RT::Line line8;
        RT::Line line9;
        RT::Line line10;
        RT::Line line11;
        RT::Line line12;

        RectangularPrism(Vector point1, Vector point2, Vector xDiff, Vector yDiff, Vector zDiff, float thickness);

    public:
        RectangularPrism(Vector point1, Vector point2, float thickness);

        void Draw(CanvasWrapper canvas, Frustum &frustum);
    };
}

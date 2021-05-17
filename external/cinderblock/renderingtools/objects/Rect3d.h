#pragma once

#include <bakkesmod/wrappers/wrapperstructs.h>
#include <bakkesmod/wrappers/canvaswrapper.h>
#include "Frustum.h"
#include "Line.h"

namespace RT
{
    class Rect3d
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

    public:
        Rect3d(Vector center, Vector size, Rotator rotation, float thickness, BakkesMod::Plugin::BakkesModPlugin *plugin);

        void Draw(CanvasWrapper &canvas, Frustum &frustum);

        void log(std::string name, BakkesMod::Plugin::BakkesModPlugin *plugin, Vector vector);
    };
}

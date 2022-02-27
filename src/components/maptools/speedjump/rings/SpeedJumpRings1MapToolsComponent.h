#pragma once

#include "../../MapToolsComponent.h"

class SpeedJumpRings1MapToolsComponent : public MapToolsComponent
{
public:
    explicit SpeedJumpRings1MapToolsComponent(NetcodePlugin *plugin);

protected:
    void resetMap() override;
    void checkpoint(int checkpoint) override;
};

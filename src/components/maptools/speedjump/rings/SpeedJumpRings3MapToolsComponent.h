#pragma once

#include "../../MapToolsComponent.h"

class SpeedJumpRings3MapToolsComponent : public MapToolsComponent
{
public:
    explicit SpeedJumpRings3MapToolsComponent(NetcodePlugin *plugin);

protected:
    void resetMap() override;
    void checkpoint(int checkpoint) override;
};

#pragma once

#include "../../MapToolsComponent.h"

class SpeedJumpRings2MapToolsComponent : public MapToolsComponent
{
public:
    explicit SpeedJumpRings2MapToolsComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

protected:
    void resetMap() override;
    void checkpoint(int checkpoint) override;
};

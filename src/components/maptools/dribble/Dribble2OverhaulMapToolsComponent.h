#pragma once

#include "../MapToolsComponent.h"

class Dribble2OverhaulMapToolsComponent : public MapToolsComponent
{
public:
    explicit Dribble2OverhaulMapToolsComponent(NetcodePlugin* plugin);

protected:
    void resetMap() override;
    void checkpoint(int checkpoint) override;
};
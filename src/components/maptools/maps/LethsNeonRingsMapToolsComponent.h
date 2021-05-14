#pragma once

#include "../MapToolsComponent.h"

class LethsNeonRingsMapToolsComponent : public MapToolsComponent
{
public:
    explicit LethsNeonRingsMapToolsComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

protected:
    void resetMap() override;
    void checkpoint(int checkpoint) override;
};

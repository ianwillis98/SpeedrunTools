#pragma once

#include "../MapToolsComponent.h"

class LethsGiantRingsMapToolsComponent : public MapToolsComponent
{
public:
    explicit LethsGiantRingsMapToolsComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

protected:
    void resetMap() override;
    void checkpoint(int checkpoint) override;
};

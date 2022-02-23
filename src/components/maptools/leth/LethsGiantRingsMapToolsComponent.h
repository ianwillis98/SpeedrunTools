#pragma once

#include "../MapToolsComponent.h"

class LethsGiantRingsMapToolsComponent : public MapToolsComponent
{
public:
    explicit LethsGiantRingsMapToolsComponent(NetcodePlugin *plugin);

protected:
    void resetMap() override;
    void checkpoint(int checkpoint) override;
};

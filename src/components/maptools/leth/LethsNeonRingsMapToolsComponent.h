#pragma once

#include "../MapToolsComponent.h"

class LethsNeonRingsMapToolsComponent : public MapToolsComponent
{
public:
    explicit LethsNeonRingsMapToolsComponent(NetcodePlugin *plugin);

protected:
    void resetMap() override;
    void checkpoint(int checkpoint) override;
};

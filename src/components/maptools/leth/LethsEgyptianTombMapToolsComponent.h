#pragma once

#include "../MapToolsComponent.h"

class LethsEgyptianTombMapToolsComponent : public MapToolsComponent
{
public:
    explicit LethsEgyptianTombMapToolsComponent(NetcodePlugin* plugin);

protected:
    void resetMap() override;
    void checkpoint(int checkpoint) override;
};
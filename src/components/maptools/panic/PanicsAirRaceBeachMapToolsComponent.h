#pragma once

#include "../MapToolsComponent.h"

class PanicsAirRaceBeachMapToolsComponent : public MapToolsComponent
{
public:
    explicit PanicsAirRaceBeachMapToolsComponent(NetcodePlugin *plugin);

protected:
    void resetMap() override;
    void checkpoint(int checkpoint) override;

private:
    void setCheckpointAndCount(int checkpoint, int count);
};

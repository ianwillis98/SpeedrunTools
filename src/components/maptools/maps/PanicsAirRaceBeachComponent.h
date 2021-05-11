#pragma once

#include "../../PluginComponentBase.h"
#include "../MapToolsModel.h"
#include "../autosplitter/runs/PanicsAirRaceBeachAutoSplitterComponent.h"

class PanicsAirRaceBeachComponent : public PluginComponentBase
{
private:
    MapToolsModel &mapToolsModel;
    PanicsAirRaceBeachAutoSplitterComponent panicsAirRaceBeachAutoSplitterComponent;

public:
    explicit PanicsAirRaceBeachComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void render() override;
    void onEvent(const std::string &eventName, bool post, void *params) override;

private:
    void renderPracticeSegments();

    void resetMap();
    void teleportToCheckpoint(int checkpoint);

    void setCheckpointAndCount(int checkpoint, int count);
};

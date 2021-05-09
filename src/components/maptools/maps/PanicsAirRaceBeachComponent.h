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
    void teleportToCheckpoint1();
    void teleportToCheckpoint2();
    void teleportToCheckpoint3();
    void teleportToCheckpoint4();
    void teleportToCheckpoint5();
    void teleportToCheckpoint6();
    void teleportToCheckpoint7();
    void teleportToCheckpoint8();
    void teleportToCheckpoint9();
    void teleportToCheckpoint10();
    void teleportToCheckpoint11();

    void setCheckpointAndCount(int checkpoint, int count);
};

#pragma once

#include "../PluginComponentBase.h"
#include "MapToolsModel.h"
#include "autosplitter/AutoSplitterComponent.h"

class MapToolsComponent : public PluginComponentBase
{
protected:
    MapToolsModel &mapToolsModel;
    std::shared_ptr<AutoSplitterComponent> autoSplitterComponent;

    const std::string mapName;
    const std::string cVarName;
    const int numCheckpoints;

public:
    MapToolsComponent(BakkesMod::Plugin::BakkesModPlugin *plugin, std::shared_ptr<AutoSplitterComponent> component,
                      std::string mapName, std::string cVarName, int numCheckpoints);

    void render() override;
    void renderCanvas(CanvasWrapper &canvasWrapper) override;
    void onEvent(const std::string &eventName, bool post, void *params) override;

    std::string getMapName();

protected:
    virtual void createResetNotifier();
    virtual void createCheckpointNotifiers();

    virtual void renderGeneralMapTools();
    virtual void renderCheckpoints();
    virtual void renderAutoSplitter();

    virtual void resetMap() = 0;
    virtual void checkpoint(int checkpoint) = 0;
};

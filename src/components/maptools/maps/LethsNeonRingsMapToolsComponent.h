#pragma once

#include "../MapToolsComponent.h"
#include "../../autosplitter/runs/LethsNeonRingsAutoSplitterComponent.h"

class LethsNeonRingsMapToolsComponent : public PluginComponentBase
{
private:
    LethsNeonRingsAutoSplitterComponent autoSplitterComponent;

public:
    explicit LethsNeonRingsMapToolsComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void render() override;
    void onEvent(const std::string &eventName, bool post, void *params) override;

private:
    void resetMap();
    void level(int level);
};

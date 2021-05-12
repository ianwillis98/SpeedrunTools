#pragma once

#include "../../PluginComponentBase.h"
#include "../MapToolsModel.h"
#include "../autosplitter/runs/TutorialAdvancedAutoSplitterComponent.h"

class TutorialAdvancedComponent : public PluginComponentBase
{
private:
    MapToolsModel &mapToolsModel;
    TutorialAdvancedAutoSplitterComponent tutorialAdvancedAutoSplitterComponent;

public:
    explicit TutorialAdvancedComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void render() override;
    void onEvent(const std::string &eventName, bool post, void *params) override;

private:
    void renderPracticeSegments();

    void loadAdvancedTutorial();
    void practiceSegment(int segment);
};

#pragma once

#include "../../PluginComponentBase.h"
#include "../autosplitter/runs/TutorialBasicAutoSplitterComponent.h"
#include "../MapToolsModel.h"

class TutorialBasicComponent : public PluginComponentBase
{
private:
    MapToolsModel &mapToolsModel;
    TutorialBasicAutoSplitterComponent tutorialBasicAutoSplitterComponent;

public:
    explicit TutorialBasicComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void render() override;
    void onEvent(const std::string &eventName, bool post, void *params) override;

private:
    void renderPracticeSegments();

    void practiceSegment1();
    void practiceSegment2();
    void practiceSegment3();
    void practiceSegment4();
    void practiceSegment5();
    void practiceSegment6();
};


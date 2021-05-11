#pragma once

#include "../../PluginComponentBase.h"
#include "../MapToolsModel.h"

class TutorialAdvancedComponent : public PluginComponentBase
{
private:
    MapToolsModel &mapToolsModel;

public:
    explicit TutorialAdvancedComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void render() override;

private:
    void renderPracticeSegments();

    void loadAdvancedTutorial();
    void practiceSegment(int segment);
};

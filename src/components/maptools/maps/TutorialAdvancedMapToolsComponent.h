#pragma once

#include "../MapToolsComponent.h"

class TutorialAdvancedMapToolsComponent : public MapToolsComponent
{
public:
    explicit TutorialAdvancedMapToolsComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

protected:
    void resetMap() override;
    void checkpoint(int checkpoint) override;
};

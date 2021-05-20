#pragma once

#include "../MapToolsComponent.h"

class TutorialBasicMapToolsComponent : public MapToolsComponent
{
public:
    explicit TutorialBasicMapToolsComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

protected:
    void resetMap() override;
    void checkpoint(int checkpoint) override;
};


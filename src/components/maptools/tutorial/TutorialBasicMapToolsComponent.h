#pragma once

#include "../MapToolsComponent.h"

class TutorialBasicMapToolsComponent : public MapToolsComponent
{
public:
    explicit TutorialBasicMapToolsComponent(NetcodePlugin *plugin);

protected:
    void resetMap() override;
    void checkpoint(int checkpoint) override;
};


#pragma

#include "../../MapToolsComponent.h"

class SpeedJumpTrials1MapToolsComponent : public MapToolsComponent
{
public:
    explicit SpeedJumpTrials1MapToolsComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

protected:
    void resetMap() override;
    void checkpoint(int checkpoint) override;
};
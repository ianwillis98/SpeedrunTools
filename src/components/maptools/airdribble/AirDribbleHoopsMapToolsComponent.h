#include "../MapToolsComponent.h"

class AirDribbleHoopsMapToolsComponent : public MapToolsComponent
{
public:
    explicit AirDribbleHoopsMapToolsComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

protected:
    void resetMap() override;
    void checkpoint(int checkpoint) override;
};

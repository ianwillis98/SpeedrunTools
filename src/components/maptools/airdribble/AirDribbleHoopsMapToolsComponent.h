#include "../MapToolsComponent.h"

class AirDribbleHoopsMapToolsComponent : public MapToolsComponent
{
public:
    explicit AirDribbleHoopsMapToolsComponent(NetcodePlugin *plugin);

protected:
    void resetMap() override;
    void checkpoint(int checkpoint) override;
};

#include "../MapToolsComponent.h"

class MinigolfMapToolsComponent : public MapToolsComponent
{
public:
    explicit MinigolfMapToolsComponent(NetcodePlugin* plugin);

protected:
    void resetMap() override;
    void checkpoint(int checkpoint) override;
};
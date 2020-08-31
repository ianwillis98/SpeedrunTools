#include "../PluginToolkit.h"
#include "../../components/game/GameGravityComponent.h"
#include "../../components/game/GameSpeedComponent.h"
#include "../../components/car/BoostComponent.h"
#include "../../components/car/AirRollComponent.h"

class MutatorsToolkit : public PluginToolkit
{
public:
    explicit MutatorsToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin);

    std::string title() override;
    void onLoad() override;
    void onUnload() override;
    void render() override;

private:
    GameGravityComponent gameGravityComponent;
    GameSpeedComponent gameSpeedComponent;
    BoostComponent boostComponent;
    AirRollComponent autoAirRollComponent;
};

#include "../PluginToolkit.h"
#include "../../components/game/GameGravityComponent.h"
#include "../../components/game/GameSpeedComponent.h"

class GameToolkit : public PluginToolkit
{
public:
    explicit GameToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin);

    std::string title() override;
    void onLoad() override;
    void onUnload() override;
    void render() override;

private:
    GameGravityComponent gameGravityComponent;
    GameSpeedComponent gameSpeedComponent;
};

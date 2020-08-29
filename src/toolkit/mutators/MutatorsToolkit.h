#include "../PluginToolkit.h"
#include "../../components/game/GameGravityComponent.h"
#include "../../components/game/GameSpeedComponent.h"

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
};

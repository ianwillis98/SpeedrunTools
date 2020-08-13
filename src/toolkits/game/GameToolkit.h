#include "../PluginToolkit.h"

class GameToolkit : public PluginToolkit
{
public:
    explicit GameToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin);

    std::string title() override;
    void onLoad() override;
    void onUnload() override;
    void render() override;

private:
    void setGameGravity(float gameGravity);
    void setGameSpeed(float gameSpeed);

    void renderGameGravityView();
    void renderGameSpeedView();
};

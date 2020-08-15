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
    std::shared_ptr<float> svSoccarGameGravity;
    std::shared_ptr<float> svSoccarGameSpeed;

    void setGameGravity(float gravity);
    void setGameSpeed(float speed);

    void renderGameGravityView();
    void renderGameSpeedView();
};

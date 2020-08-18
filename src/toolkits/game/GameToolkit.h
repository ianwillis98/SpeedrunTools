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
    std::shared_ptr<float> gameGravity;

    std::shared_ptr<float> svSoccarGameSpeed;
    std::shared_ptr<float> gameSpeed;

    void setSvSoccarGameGravity(float gravity);
    void setGameGravity(float gravity);

    void setSvSoccarGameSpeed(float speed);
    void setGameSpeed(float speed);

    void renderGameGravityView();
    void renderGameSpeedView();
};

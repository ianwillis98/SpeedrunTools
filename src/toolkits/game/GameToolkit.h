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
    void setSvSoccarGameGravity(float gravity);
    void setGameGravity(float gravity);
    void renderGameGravityView();

    std::shared_ptr<float> svSoccarGameSpeed;
    std::shared_ptr<float> gameSpeed;
    void setSvSoccarGameSpeed(float speed);
    void setGameSpeed(float speed);
    void renderGameSpeedView();
};

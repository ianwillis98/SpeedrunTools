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

    void setSvSoccarGameGravityCVar(float gravity);
    void onSvSoccarGameGravityCVarChanged(const std::string &oldValue, const CVarWrapper &cvar);

    void setGameGravityCVar(float gravity);
    void onGameGravityCVarChanged(const std::string &oldValue, const CVarWrapper &cvar);

    void setSvSoccarGameSpeedCVar(float speed);
    void onSvSoccarGameSpeedCVarChanged(const std::string &oldValue, const CVarWrapper &cvar);

    void setGameSpeedCVar(float speed);
    void onGameSpeedCVarChanged(const std::string &oldValue, const CVarWrapper &cvar);

    void renderGameGravityView();
    void renderGameSpeedView();
};

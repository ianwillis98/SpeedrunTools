#pragma once

#include "../PluginToolkit.h"

class TestToolkit : public PluginToolkit
{
public:
    explicit TestToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin);

    std::string title() override;
    void onLoad() override;
    void onUnload() override;
    void render() override;

private:
    std::shared_ptr<float> gravity;

    void setGameGravity(float g);
};

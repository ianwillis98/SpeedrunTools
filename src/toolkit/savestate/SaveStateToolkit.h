#pragma once

#include "../PluginToolkit.h"
#include "../../components/savestate/SaveStateComponent.h"

class SaveStateToolkit : public PluginToolkit
{
public:
    explicit SaveStateToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin);

    std::string title() override;
    void onLoad() override;
    void onUnload() override;
    void render() override;

private:
    SaveStateComponent saveStateComponent;
};

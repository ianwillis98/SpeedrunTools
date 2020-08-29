#pragma once

#include "../PluginToolkit.h"
#include "../../components/savestate/SaveStateComponent.h"
#include "../../components/savestate/RewindStateComponent.h"

class SaveStateToolkit : public PluginToolkit
{
public:
    explicit SaveStateToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin);

    std::string title() override;
    void onLoad() override;
    void onUnload() override;
    void render() override;

private:
    RewindStateComponent rewindStateComponent;
    SaveStateComponent saveStateComponent;
};

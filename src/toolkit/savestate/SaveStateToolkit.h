#pragma once

#include "../PluginToolkit.h"
#include "../../component/savestate/SaveStateComponent.h"
#include "../../component/savestate/RewindStateComponent.h"

class SaveStateToolkit : public PluginToolkit
{
private:
    RewindStateComponent rewindStateComponent;
    SaveStateComponent saveStateComponent;

public:
    explicit SaveStateToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin);

    std::string title() override;
    void onLoad() override;
    void onUnload() override;
    void render() override;
};

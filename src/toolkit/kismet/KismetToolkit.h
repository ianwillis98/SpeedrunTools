#pragma once

#include "../PluginToolkit.h"
#include "../../component/kismet/SequenceVariableComponent.h"

class KismetToolkit : public PluginToolkit
{
private:
    SequenceVariableComponent sequenceVariableComponent;

public:
    explicit KismetToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin);

    std::string title() override;
    void onLoad() override;
    void onUnload() override;
    void render() override;

private:
    void onListSequenceVars();
};

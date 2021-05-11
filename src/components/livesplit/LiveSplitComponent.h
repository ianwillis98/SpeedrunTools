#pragma once

#include "LiveSplitModel.h"
#include "../PluginComponentBase.h"
#include "../../services/LiveSplitClient.h"

class LiveSplitComponent : public PluginComponentBase
{
private:
    LiveSplitModel &liveSplitModel;

public:
    explicit LiveSplitComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void render() override;

private:
    void renderConnectionStatus();
    void renderRemoteControls();
};

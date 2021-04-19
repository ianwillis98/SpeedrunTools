#pragma once

#include "../PluginController.h"
#include "LiveSplitModel.h"
#include "LiveSplitConnectView.h"

class LiveSplitController : public PluginController
{
private:
    std::shared_ptr<LiveSplitModel> model;
    LiveSplitConnectView connectView;

public:
    LiveSplitController(BakkesMod::Plugin::BakkesModPlugin *plugin, std::shared_ptr<LiveSplitModel> model);

    void onLoad() override;
    void render() override;
};

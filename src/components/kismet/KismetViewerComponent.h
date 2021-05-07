#pragma once

#include "../PluginComponentBase.h"
#include "../../models/KismetSequenceVariable.h"

class KismetViewerComponent : public PluginComponentBase
{
private:
    std::vector<KismetSequenceVariable> kismetVars;
    int selectedRow;
    bool autoRefresh;

public:
    explicit KismetViewerComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void render() override;
    void onEvent(const std::string &eventName, bool post, void *params) override;

private:
    void loadSequenceVariables();
    void autoRefreshFunc();
};
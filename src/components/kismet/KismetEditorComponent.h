#pragma once

#include "../PluginComponentBase.h"
#include "../../models/KismetSequenceVariable.h"

class KismetEditorComponent : public PluginComponentBase
{
private:
    std::vector<KismetSequenceVariable> kismetVars;
    bool shouldAutoReloadKismetVars;
    std::mutex mutex;

public:
    explicit KismetEditorComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void render() override;
    void onEvent(const std::string &eventName, bool post, void *params) override;

private:
    void loadKismetVars();
};

#pragma once

#include "../PluginComponentBase.h"
#include "../../models/KismetSequenceVariable.h"

class KismetEditorComponent : public PluginComponentBase
{
private:
    static const std::string ListAllCVarsNotifier;

private:
    std::vector<KismetSequenceVariable> kismetVars;
    bool shouldAutoReloadKismetVars;
    std::mutex mutex;

public:
    explicit KismetEditorComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onEvent(const std::string &eventName, bool post, void *params) override;
    void render() override;

private:
    std::vector<KismetSequenceVariable> loadKismetVars();
    void updateKismetVars();
    void clearKismetVars();
    void listCVarsToConsole();
};

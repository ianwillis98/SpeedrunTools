#pragma once

#include "../PluginComponentBase.h"
#include "KismetModel.h"
#include "../../models/KismetVar.h"

class KismetEditorComponent : public PluginComponentBase
{
private:
    static const std::string ListAllCVarsNotifier;

private:
    KismetModel &kismetModel;

public:
    explicit KismetEditorComponent(NetcodePlugin *plugin);

    void onEvent(const std::string &eventName, bool post, void *params) override;
    void render() override;

private:
    void listCVarsToConsole();
};

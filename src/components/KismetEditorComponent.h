#pragma once

#include <sstream>
#include <map>
#include <bakkesmod/wrappers/kismet/SequenceWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceVariableWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceOpWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceObjectWrapper.h>
#include "../PluginComponent.h"
#include "../models/KismetSequenceVariable.h"

class KismetEditorComponent : public PluginComponent
{
private:
    std::vector<KismetSequenceVariable> kismetVars;
    int selectedRow;

public:
    explicit KismetEditorComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    std::string title() override;
    void onLoad() override;
    void render() override;

private:
    void listSequenceVars();
    void loadSequenceVariables();
};

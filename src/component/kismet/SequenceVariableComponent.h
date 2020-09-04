#pragma once

#include <map>
#include <bakkesmod/wrappers/kismet/SequenceWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceVariableWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceOpWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceObjectWrapper.h>
#include "../PluginComponent.h"
#include "../../models/KismetSequenceVariable.h"

class SequenceVariableComponent : public PluginComponent
{
private:
    std::vector<KismetSequenceVariable> variables;
    int selectedRow;

public:
    explicit SequenceVariableComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onLoad() override;
    void onUnload() override;
    void render() override;

private:
    void loadSequenceVariables();
};

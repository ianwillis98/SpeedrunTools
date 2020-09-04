#pragma once

#include <sstream>
#include <iostream>
#include <fstream>
#include <map>
#include <bakkesmod/wrappers/kismet/SequenceWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceVariableWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceOpWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceObjectWrapper.h>
#include "../PluginToolkit.h"

class TestToolkit : public PluginToolkit
{
public:
    explicit TestToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin);

    std::string title() override;
    void onLoad() override;
    void onUnload() override;
    void render() override;

private:
    std::stringstream recursiveList(SequenceWrapper sequence);
};

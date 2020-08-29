#pragma once

#include "../plugin/PluginComponent.h"

class PluginToolkit : public PluginComponent
{
public:
    explicit PluginToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin);

    virtual std::string title() = 0;
};

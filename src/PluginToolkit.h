#pragma once

#include "PluginComponent.h"

class PluginToolkit : public PluginComponent
{
public:
    virtual std::string title() = 0;
};
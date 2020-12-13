#pragma once

#include <bakkesmod/plugin/bakkesmodplugin.h>
#include "AutoSplitter.h"

class AutoSplitterBase : public AutoSplitter
{
protected:
    BakkesMod::Plugin::BakkesModPlugin *plugin{};

public:
    explicit AutoSplitterBase(BakkesMod::Plugin::BakkesModPlugin *plugin);
};

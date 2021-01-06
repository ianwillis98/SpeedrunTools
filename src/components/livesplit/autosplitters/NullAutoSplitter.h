#pragma once

#include "AutoSplitterBase.h"

class NullAutoSplitter : public AutoSplitterBase
{
public:
    NullAutoSplitter();

    bool update() override;
};

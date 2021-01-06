#include "NullAutoSplitter.h"

NullAutoSplitter::NullAutoSplitter() : AutoSplitterBase(nullptr)
{

}

bool NullAutoSplitter::update()
{
    return false;
}

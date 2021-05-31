#include "TestVar.h"

TestVar::TestVar(SequenceVariableWrapper &var) : var(var)
{

}

std::string TestVar::getName()
{
    return this->var.GetVarName();
}

std::string TestVar::getValue()
{
    return this->var.GetString();
}


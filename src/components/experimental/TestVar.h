#pragma once

class TestVar
{
private:
    SequenceVariableWrapper &var;

public:
    explicit TestVar(SequenceVariableWrapper &var);

    std::string getName();
    std::string getValue();
};

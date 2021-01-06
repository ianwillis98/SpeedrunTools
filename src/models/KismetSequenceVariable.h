#pragma once

#include <map>
#include <bakkesmod/wrappers/wrapperstructs.h>
#include <bakkesmod/wrappers/kismet/SequenceWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceVariableWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceOpWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceObjectWrapper.h>
#include <bakkesmod/wrappers/Engine/UnrealStringWrapper.h>

enum class KismetSequenceVariableType
{
    Bool,
    Int,
    Float,
    Vector,
    String,
    ObjectList,
    Actor,
    Unknown
};

class KismetSequenceVariable
{
private:
    std::string name;

    KismetSequenceVariableType type;
    bool boolValue;
    int intValue;
    float floatValue;
    struct Vector vectorValue;
    std::string stringValue;

public:
    explicit KismetSequenceVariable(SequenceVariableWrapper var);

    KismetSequenceVariableType getType();

    std::string getName();

    bool getBoolValue() const;
    int getIntValue() const;
    float getFloatValue() const;
    struct Vector getVectorValue();
    std::string getStringValue();

    std::string getValueAsString();
    std::string getTypeAsString();
};

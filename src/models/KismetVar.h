#pragma once

#include <bakkesmod/wrappers/wrapperstructs.h>
#include <bakkesmod/wrappers/kismet/SequenceWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceVariableWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceOpWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceObjectWrapper.h>
#include <bakkesmod/wrappers/Engine/UnrealStringWrapper.h>

enum class KismetVarType
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

class KismetVar
{
private:
    std::string name;

    KismetVarType type;
    bool boolValue;
    int intValue;
    float floatValue;
    struct Vector vectorValue;
    std::string stringValue;

public:
    explicit KismetVar(std::string name);
    explicit KismetVar(SequenceVariableWrapper var);

    std::string getName() const;

    bool render();

    KismetVarType getType() const;
    bool getBoolValue() const;
    int getIntValue() const;
    float getFloatValue() const;
    struct Vector getVectorValue() const;
    std::string getStringValue() const;

    void setBoolValue(bool value);
    void setIntValue(int value);
    void setFloatValue(float value);
    void setStringValue(const std::string &value);

    std::string getTypeAsString();
    std::string getValueAsString();
};

#pragma once

#include <map>
#include <bakkesmod/plugin/bakkesmodplugin.h>
#include <bakkesmod/wrappers/wrapperstructs.h>
#include <bakkesmod/wrappers/kismet/SequenceWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceVariableWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceOpWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceObjectWrapper.h>
#include <bakkesmod/wrappers/Engine/UnrealStringWrapper.h>
#include <imgui.h>

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
    BakkesMod::Plugin::BakkesModPlugin *plugin;

    std::string name;

    KismetSequenceVariableType type;
    bool boolValue;
    int intValue;
    float floatValue;
    struct Vector vectorValue;
    std::string stringValue;

public:
    KismetSequenceVariable(BakkesMod::Plugin::BakkesModPlugin *plugin, SequenceVariableWrapper var);

    std::string getName() const;

    KismetSequenceVariableType getType() const;
    bool getBoolValue() const;
    int getIntValue() const;
    float getFloatValue() const;
    struct Vector getVectorValue() const;
    std::string getStringValue() const;

    void setBoolValue(bool value);
    void setIntValue(int value);
    void setFloatValue(float value);

    std::string getValueAsString();
    std::string getTypeAsString();

    bool render();

    void updateMainSequenceValue() const;
};

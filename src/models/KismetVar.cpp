#include "KismetVar.h"

#include <utility>

KismetVar::KismetVar(std::string name)
        : name(std::move(name)),
          type(KismetVarType::Unknown),
          boolValue(false),
          intValue(0),
          floatValue(0.0f),
          vectorValue(),
          stringValue()
{

}

KismetVar::KismetVar(SequenceVariableWrapper var)
        : KismetVar(var.GetVarName())
{
    if (var.memory_address == NULL) return;

    if (var.IsBool())
    {
        this->type = KismetVarType::Bool;
        this->boolValue = var.GetBool();
    }
    else if (var.IsInt())
    {
        this->type = KismetVarType::Int;
        this->intValue = var.GetInt();
    }
    else if (var.IsFloat())
    {
        this->type = KismetVarType::Float;
        this->floatValue = var.GetFloat();
    }
    else if (var.IsVector())
    {
        this->type = KismetVarType::Vector;
        this->vectorValue = var.GetVector();
    }
    else if (var.IsString())
    {
        this->type = KismetVarType::String;
        this->stringValue = var.GetString();
    }
    else if (var.IsObjectList())
    {
        this->type = KismetVarType::ObjectList;
        this->stringValue = "Its an object list";
    }
    else if (var.IsActor())
    {
        this->type = KismetVarType::Actor;
        this->stringValue = "Its an actor";
    }
    else
    {
        this->type = KismetVarType::Unknown;
    }
}

std::string KismetVar::getName() const
{
    return this->name;
}

bool KismetVar::render()
{
    if (this->type == KismetVarType::Int)
    {
        return ImGui::InputInt(("##" + this->name).c_str(), &this->intValue, 1, 1, ImGuiInputTextFlags_EnterReturnsTrue);
    }
    if (this->type == KismetVarType::Float)
    {
        return ImGui::InputFloat(("##" + this->name).c_str(), &this->floatValue, 1.0f, 1.0f, "%.3f", ImGuiInputTextFlags_EnterReturnsTrue);
    }
    if (this->type == KismetVarType::Bool)
    {
        return ImGui::Checkbox(("##" + this->name).c_str(), &this->boolValue);
    }

    ImGui::AlignTextToFramePadding();
    ImGui::Text("%s", this->getValueAsString().c_str());
    return false;
}

KismetVarType KismetVar::getType() const
{
    return this->type;
}

bool KismetVar::getBoolValue() const
{
    return this->boolValue;
}

void KismetVar::setBoolValue(bool value)
{
    this->boolValue = value;
}

int KismetVar::getIntValue() const
{
    return this->intValue;
}

void KismetVar::setIntValue(int value)
{
    this->intValue = value;
}

float KismetVar::getFloatValue() const
{
    return this->floatValue;
}

void KismetVar::setFloatValue(float value)
{
    this->floatValue = value;
}

struct Vector KismetVar::getVectorValue() const
{
    return this->vectorValue;
}

std::string KismetVar::getStringValue() const
{
    return this->stringValue;
}

void KismetVar::setStringValue(const std::string &value)
{
    this->stringValue = value;
}

std::string KismetVar::getTypeAsString()
{
    switch (this->type)
    {
        case KismetVarType::Bool:
            return "bool";
        case KismetVarType::Int:
            return "int";
        case KismetVarType::Float:
            return "float";
        case KismetVarType::Vector:
            return "Vector";
        case KismetVarType::String:
            return "string";
        case KismetVarType::ObjectList:
            return "Object List";
        case KismetVarType::Actor:
            return "Actor";
        case KismetVarType::Unknown:
            return "Unknown";
        default:
            return "Type Not Registered";
    }
}

std::string KismetVar::getValueAsString()
{
    switch (this->type)
    {
        case KismetVarType::Bool:
            return this->boolValue ? "true" : "false";
        case KismetVarType::Int:
            return std::to_string(this->intValue);
        case KismetVarType::Float:
            return std::to_string(this->floatValue);
        case KismetVarType::Vector:
            return "Vec(" + std::to_string(this->vectorValue.X) + ", " + std::to_string(this->vectorValue.Y) + ", " +
                   std::to_string(this->vectorValue.Z) + ")";
        case KismetVarType::String:
        case KismetVarType::ObjectList:
        case KismetVarType::Actor:
            return this->stringValue;
        case KismetVarType::Unknown:
            return "Unknown";
        default:
            return "Type Not Registered";
    }
}

//void KismetVar::updateMainSequenceValue() const
//{
//    auto sequence = this->plugin->gameWrapper->GetMainSequence();
//    if (sequence.memory_address == NULL) return;
//
//    auto vars = sequence.GetAllSequenceVariables(false);
//
//    auto var = vars.find(this->name);
//    if (var == vars.end()) return;
//
//    if (this->type == KismetVarType::Int)
//    {
//        var->second.SetInt(this->intValue);
//    }
//    if (this->type == KismetVarType::Float)
//    {
//        var->second.SetFloat(this->floatValue);
//    }
//    if (this->type == KismetVarType::Bool)
//    {
//        var->second.SetBool(this->boolValue);
//    }
//}

#include "KismetSequenceVariable.h"

KismetSequenceVariable::KismetSequenceVariable(BakkesMod::Plugin::BakkesModPlugin *plugin, SequenceVariableWrapper var)
        : plugin(plugin),
          name(),
          boolValue(false),
          intValue(0),
          floatValue(0.0f),
          stringValue(),
          vectorValue()
{
    if (var.memory_address == NULL) return;

    this->name = var.GetVarName();

    if (var.IsBool())
    {
        this->type = KismetSequenceVariableType::Bool;
        this->boolValue = var.GetBool();
    }
    else if (var.IsInt())
    {
        this->type = KismetSequenceVariableType::Int;
        this->intValue = var.GetInt();
    }
    else if (var.IsFloat())
    {
        this->type = KismetSequenceVariableType::Float;
        this->floatValue = var.GetFloat();
    }
    else if (var.IsVector())
    {
        this->type = KismetSequenceVariableType::Vector;
        this->vectorValue = var.GetVector();
    }
    else if (var.IsString())
    {
        this->type = KismetSequenceVariableType::String;
        this->stringValue = var.GetString();
    }
    else if (var.IsObjectList())
    {
        this->type = KismetSequenceVariableType::ObjectList;
        this->stringValue = "Its an object list";
    }
    else if (var.IsActor())
    {
        this->type = KismetSequenceVariableType::Actor;
        this->stringValue = "Its an actor";
    }
    else
    {
        this->type = KismetSequenceVariableType::Unknown;
    }
}

std::string KismetSequenceVariable::getName() const
{
    return this->name;
}

KismetSequenceVariableType KismetSequenceVariable::getType() const
{
    return this->type;
}

bool KismetSequenceVariable::getBoolValue() const
{
    return this->boolValue;
}

int KismetSequenceVariable::getIntValue() const
{
    return this->intValue;
}

float KismetSequenceVariable::getFloatValue() const
{
    return this->floatValue;
}

struct Vector KismetSequenceVariable::getVectorValue() const
{
    return this->vectorValue;
}

std::string KismetSequenceVariable::getStringValue() const
{
    return this->stringValue;
}

std::string KismetSequenceVariable::getValueAsString()
{
    switch (this->type)
    {
        case KismetSequenceVariableType::Bool:
            return this->boolValue ? "true" : "false";
        case KismetSequenceVariableType::Int:
            return std::to_string(this->intValue);
        case KismetSequenceVariableType::Float:
            return std::to_string(this->floatValue);
        case KismetSequenceVariableType::Vector:
            return "Vec(" + std::to_string(this->vectorValue.X) + ", " + std::to_string(this->vectorValue.Y) + ", " +
                   std::to_string(this->vectorValue.Z) + ")";
        case KismetSequenceVariableType::String:
            return this->stringValue;
        case KismetSequenceVariableType::ObjectList:
            return this->stringValue;
        case KismetSequenceVariableType::Actor:
            return this->stringValue;
        case KismetSequenceVariableType::Unknown:
            return "Unknown";
        default:
            return "Type Not Registered";
    }
}
std::string KismetSequenceVariable::getTypeAsString()
{
    switch (this->type)
    {
        case KismetSequenceVariableType::Bool:
            return "bool";
        case KismetSequenceVariableType::Int:
            return "int";
        case KismetSequenceVariableType::Float:
            return "float";
        case KismetSequenceVariableType::Vector:
            return "Vector";
        case KismetSequenceVariableType::String:
            return "string";
        case KismetSequenceVariableType::ObjectList:
            return "Object List";
        case KismetSequenceVariableType::Actor:
            return "Actor";
        case KismetSequenceVariableType::Unknown:
            return "Unknown";
        default:
            return "Type Not Registered";
    }
}

bool KismetSequenceVariable::render()
{
    if (this->type == KismetSequenceVariableType::Int)
    {
        return ImGui::InputInt(("##" + this->name).c_str(), &this->intValue, 1, 1, ImGuiInputTextFlags_EnterReturnsTrue);
    }
    if (this->type == KismetSequenceVariableType::Float)
    {
        return ImGui::InputFloat(("##" + this->name).c_str(), &this->floatValue, 1.0f, 1.0f, "%.3f", ImGuiInputTextFlags_EnterReturnsTrue);
    }
    if (this->type == KismetSequenceVariableType::Bool)
    {
        return ImGui::Checkbox(("##" + this->name).c_str(), &this->boolValue);
    }

    ImGui::AlignTextToFramePadding();
    ImGui::Text("%s", this->getValueAsString().c_str());
    return false;
}

void KismetSequenceVariable::updateMainSequenceValue() const
{
    auto sequence = this->plugin->gameWrapper->GetMainSequence();
    if (sequence.memory_address == NULL) return;

    auto vars = sequence.GetAllSequenceVariables(false);

    auto var = vars.find(this->name);
    if (var == vars.end()) return;

    if (this->type == KismetSequenceVariableType::Int)
    {
        var->second.SetInt(this->intValue);
    }
    if (this->type == KismetSequenceVariableType::Float)
    {
        var->second.SetFloat(this->floatValue);
    }
    if (this->type == KismetSequenceVariableType::Bool)
    {
        var->second.SetBool(this->boolValue);
    }
}

#include <imgui.h>
#include <imgui_internal.h>
#include "ImGuiExtensions.h"

void ImGuiExtensions::PushDisableStyle()
{
    ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
}

void ImGuiExtensions::PopDisableStyle()
{
    ImGui::PopItemFlag();
    ImGui::PopStyleVar();
}

void ImGuiExtensions::PushDisableStyleIf(bool flag)
{
    if (flag)
    {
        ImGuiExtensions::PushDisableStyle();
    }
}

void ImGuiExtensions::PopDisableStyleIf(bool flag)
{
    if (flag)
    {
        ImGuiExtensions::PopDisableStyle();
    }
}

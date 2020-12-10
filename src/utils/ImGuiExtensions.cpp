#include <imgui.h>
#include <imgui_internal.h>
#include "ImGuiExtensions.h"

void ImGuiExtensions::PushDisabledStyle()
{
    ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
}

void ImGuiExtensions::PopDisabledStyle()
{
    ImGui::PopItemFlag();
    ImGui::PopStyleVar();
}

void ImGuiExtensions::PushDisabledStyleIf(bool flag)
{
    if (flag)
    {
        ImGuiExtensions::PushDisabledStyle();
    }
}

void ImGuiExtensions::PopDisabledStyleIf(bool flag)
{
    if (flag)
    {
        ImGuiExtensions::PopDisabledStyle();
    }
}

void ImGuiExtensions::BigSpacing()
{
    ImGui::Dummy(ImVec2(0.0f, 7.0f));
}

void ImGuiExtensions::BigSeparator()
{
    ImGuiExtensions::BigSpacing();
    ImGui::Separator();
    ImGuiExtensions::BigSpacing();
}

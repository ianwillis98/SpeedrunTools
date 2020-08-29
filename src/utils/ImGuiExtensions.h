#pragma once

class ImGuiExtensions
{
public:
    static void PushDisabledStyle();
    static void PopDisabledStyle();

    static void PushDisabledStyleIf(bool flag);
    static void PopDisabledStyleIf(bool flag);
};

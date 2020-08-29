#pragma once

class ImGuiExtensions
{
public:
    static void PushDisableStyle();
    static void PopDisableStyle();

    static void PushDisableStyleIf(bool flag);
    static void PopDisableStyleIf(bool flag);
};

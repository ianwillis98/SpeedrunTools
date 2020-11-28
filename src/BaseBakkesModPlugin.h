#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <bakkesmod/plugin/bakkesmodplugin.h>
#include <bakkesmod/plugin/pluginwindow.h>
#include <imgui.h>
#include <imgui_internal.h>

class BaseBakkesModPlugin : public BakkesMod::Plugin::BakkesModPlugin, public BakkesMod::Plugin::PluginWindow
{
protected:
    const char *menuTitle;
    const char *menuName;
    ImGuiWindowFlags flags;
    bool isMenuOpen;

public:
    BaseBakkesModPlugin(const char *menuTitle, const char *menuName, ImGuiWindowFlags flags = 0);

    virtual void renderBody() = 0;

    void Render() override;
    void SetImGuiContext(uintptr_t ctx) override;
    bool ShouldBlockInput() override;
    bool IsActiveOverlay() override;
    void OnOpen() override;
    void OnClose() override;
    std::string GetMenuName() override;
    std::string GetMenuTitle() override;
};

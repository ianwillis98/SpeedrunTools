#pragma once

#include <bakkesmod/plugin/bakkesmodplugin.h>
#include <bakkesmod/plugin/pluginwindow.h>
#include <imgui.h>

class BaseBakkesModPlugin : public BakkesMod::Plugin::BakkesModPlugin, public BakkesMod::Plugin::PluginWindow {
private:
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

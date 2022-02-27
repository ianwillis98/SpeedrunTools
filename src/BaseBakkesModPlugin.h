#pragma once

#include <bakkesmod/plugin/pluginwindow.h>
#include "NetcodePlugin.h"

class BaseBakkesModPlugin : public NetcodePlugin, public BakkesMod::Plugin::PluginWindow
{
protected:
    const std::string menuTitle;
    const std::string menuName;
    ImGuiWindowFlags flags;

    bool isMenuOpen;

public:
    BaseBakkesModPlugin(std::string menuTitle, std::string menuName, ImGuiWindowFlags flags = 0);

    virtual void renderBody() = 0;

    void Render() override;
    void OnOpen() override;
    void OnClose() override;
    void SetImGuiContext(uintptr_t ctx) override;
    bool ShouldBlockInput() override;
    bool IsActiveOverlay() override;
    std::string GetMenuName() override;
    std::string GetMenuTitle() override;
};

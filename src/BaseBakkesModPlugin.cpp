#include "BaseBakkesModPlugin.h"

#include <utility>

BaseBakkesModPlugin::BaseBakkesModPlugin(std::string menuTitle, std::string menuName, ImGuiWindowFlags flags)
        : menuTitle(std::move(menuTitle)),
          menuName(std::move(menuName)),
          flags(flags)
{
    this->isMenuOpen = false;
}

void BaseBakkesModPlugin::Render()
{
    if (ImGui::Begin(this->menuTitle.c_str(), &this->isMenuOpen, this->flags))
    {
        this->renderBody();

        if (!isMenuOpen)
        {
            this->cvarManager->executeCommand("togglemenu " + std::string(menuName));
        }
    }
    ImGui::End();
}

// Called when window is opened
void BaseBakkesModPlugin::OnOpen()
{
    this->isMenuOpen = true;
}

// Called when window is closed
void BaseBakkesModPlugin::OnClose()
{
    this->isMenuOpen = false;
}

// Don't call this yourself, BM will call this function with a pointer to the current ImGui context
void BaseBakkesModPlugin::SetImGuiContext(uintptr_t ctx)
{
    ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext *>(ctx));
}

// Should events such as mouse clicks/key inputs be blocked so they won't reach the game
bool BaseBakkesModPlugin::ShouldBlockInput()
{
    return ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard;
}

// Return true if window should be interactive
bool BaseBakkesModPlugin::IsActiveOverlay()
{
    return true;
}

// Name of the menu that is used to toggle the window.
std::string BaseBakkesModPlugin::GetMenuName()
{
    return this->menuName;
}

// Title to give the menu
std::string BaseBakkesModPlugin::GetMenuTitle()
{
    return this->menuTitle;
}
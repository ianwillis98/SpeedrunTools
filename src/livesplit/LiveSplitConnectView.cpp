#include "LiveSplitConnectView.h"

#include <utility>

LiveSplitConnectView::LiveSplitConnectView(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginView(plugin),
          connecting(false)
{

}

void LiveSplitConnectView::render()
{
    if (!connecting)
    {
        if (ImGui::Button("Connect"))
        {
            this->onConnectionButtonClickCallback();
        }
    }
    else
    {
        ImGuiExtensions::PushDisabledStyle();
        ImGui::Button("Connecting");
        ImGuiExtensions::PopDisabledStyle();
    }
}

void LiveSplitConnectView::setOnConnectButtonClickCallback(std::function<void()> callback)
{
    this->onConnectionButtonClickCallback = std::move(callback);
}

void LiveSplitConnectView::setConnecting(bool c)
{
    this->connecting = c;
}

#pragma once

#include "BaseBakkesModPlugin.h"
#include "PluginComponent.h"

class SpeedrunTools : public BaseBakkesModPlugin
{
private:
    std::vector<std::pair<std::string, std::unique_ptr<PluginComponent>>> tabs;

public:
    static const std::string PLUGIN_VERSION;
    static const std::string PLUGIN_TITLE;
    static const std::string PLUGIN_MENU_NAME;

    SpeedrunTools();

    void onLoad() override;
    void onUnload() override;

    void renderBody() override;
    void renderCanvas(CanvasWrapper &canvasWrapper);

private:
    void setupEvents();
    void setupEventPost(const std::string &eventName);
};

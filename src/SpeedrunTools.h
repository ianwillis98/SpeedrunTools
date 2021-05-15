#pragma once

#include "BaseBakkesModPlugin.h"
#include "PluginComponent.h"

class SpeedrunTools : public BaseBakkesModPlugin
{
private:
    std::vector<std::pair<std::string, std::unique_ptr<PluginComponent>>> tabs;

public:
    static const char *PLUGIN_VERSION;
    static const char *PLUGIN_TITLE;
    static const char *PLUGIN_MENU_NAME;

    SpeedrunTools();

    void onLoad() override;
    void onUnload() override;
    void renderBody() override;
    void renderCanvas(CanvasWrapper &canvasWrapper);

private:
    void setupEvents();

    void setupEvent(const std::string &eventName);
    void setupEventPost(const std::string &eventName);
};

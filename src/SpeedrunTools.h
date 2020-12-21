#pragma once

#include "BaseBakkesModPlugin.h"
#include "PluginToolkit.h"

class SpeedrunTools : public BaseBakkesModPlugin
{
private:
    std::vector<std::unique_ptr<PluginToolkit>> toolkits;

public:
    static const char *PLUGIN_VERSION;
    static const char *PLUGIN_TITLE;
    static const char *PLUGIN_MENU_NAME;

    SpeedrunTools();

    void onLoad() override;
    void onUnload() override;
    void renderBody() override;

private:
    void setupEvents();

    void setupEvent(const std::string &eventName);
    void setupEventPost(const std::string &eventName);
    void setupEventPostDelayed(const std::string &eventName, float delay);
};

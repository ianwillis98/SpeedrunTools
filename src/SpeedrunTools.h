#pragma once

#include "BaseBakkesModPlugin.h"
#include "PluginComponent.h"

class SpeedrunTools : public BaseBakkesModPlugin
{
private:
    std::vector<std::unique_ptr<PluginComponent>> components;

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
};

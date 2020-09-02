#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <bakkesmod/plugin/bakkesmodplugin.h>
#include "plugin/BaseBakkesModPlugin.h"
#include "toolkit/PluginToolkit.h"

class SpeedrunTools : public BaseBakkesModPlugin
{
public:
    static const char *PLUGIN_VERSION;
    static const char *PLUGIN_TITLE;
    static const char *PLUGIN_MENU_NAME;

    SpeedrunTools();

    void onLoad() override;
    void onUnload() override;
    void renderBody() override;

private:
    std::vector<std::unique_ptr<PluginToolkit>> toolkits;
};

#pragma once

#include "BaseBakkesModPlugin.h"
#include "PluginController.h"
#include "ObjectGraph.h"

class SpeedrunTools : public BaseBakkesModPlugin
{
private:
    ObjectGraph objects;

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
};

#pragma once

#include "PluginComponentBase.h"

class MultiComponent : public PluginComponentBase
{
private:
    std::vector<std::unique_ptr<PluginComponent>> components;

public:
    explicit MultiComponent(BakkesMod::Plugin::BakkesModPlugin *plugin, std::vector<std::unique_ptr<PluginComponent>> components);

    void onLoad() override;
    void onUnload() override;
    void render() override;
    void onEvent(const std::string &eventName, bool post, void *params) override;
};

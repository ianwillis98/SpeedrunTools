#pragma once

class PluginComponent
{
public:
    virtual void render() = 0;
    virtual void onEvent(const std::string &eventName, bool post, void *params) = 0;
};
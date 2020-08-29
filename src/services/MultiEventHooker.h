#pragma once

#include <bakkesmod/plugin/bakkesmodplugin.h>
#include <string>
#include <unordered_map>

class MultiEventHooker
{
private:
    BakkesMod::Plugin::BakkesModPlugin *plugin;

    std::unordered_map<std::string, std::vector<std::function<void(std::string)>>> eventCallbacks;
    std::unordered_map<std::string, std::vector<std::function<void(std::string)>>> eventPostCallbacks;

    explicit MultiEventHooker(BakkesMod::Plugin::BakkesModPlugin *plugin);

public:
    static MultiEventHooker &getInstance(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void hookEvent(const std::string &eventName, const std::function<void(std::string eventName)> &callback);
    void unhookEvent(const std::string &eventName);

    void hookEventPost(const std::string &eventName, const std::function<void(std::string eventName)> &callback);
    void unhookEventPost(const std::string &eventName);

private:
    void handleEventCallback(const std::string &eventName);
    void handleEventPostCallback(const std::string &eventName);
};

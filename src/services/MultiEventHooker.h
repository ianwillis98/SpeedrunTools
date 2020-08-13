#pragma once

#include <bakkesmod/plugin/bakkesmodplugin.h>
#include <string>
#include <unordered_map>

class MultiEventHooker {
private:
    std::unordered_map<std::string, std::vector<std::function<void(std::string)>>> eventCallbacks;
    std::unordered_map<std::string, std::vector<std::function<void(std::string)>>> eventPostCallbacks;

    MultiEventHooker();

public:
    static MultiEventHooker &getInstance();

    void hookEvent(BakkesMod::Plugin::BakkesModPlugin *plugin, const std::string &eventName, const std::function<void(std::string eventName)> &callback);
    void unhookEvent(BakkesMod::Plugin::BakkesModPlugin *plugin, const std::string &eventName);
    void handleEventCallback(const std::string &eventName);

    void hookEventPost(BakkesMod::Plugin::BakkesModPlugin *plugin, const std::string &eventName, const std::function<void(std::string eventName)> &callback);
    void unhookEventPost(BakkesMod::Plugin::BakkesModPlugin *plugin, const std::string &eventName);
    void handleEventPostCallback(const std::string &eventName);

};



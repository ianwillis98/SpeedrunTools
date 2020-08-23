#include "MultiEventHooker.h"

MultiEventHooker &MultiEventHooker::getInstance() {
    static MultiEventHooker instance;
    return instance;
}

MultiEventHooker::MultiEventHooker() : eventCallbacks() {
}

void MultiEventHooker::hookEvent(BakkesMod::Plugin::BakkesModPlugin *plugin, const std::string &eventName,
                                 const std::function<void(std::string)> &callback) {
    if (eventCallbacks.find(eventName) == eventCallbacks.end()) {
        std::vector<std::function<void(std::string)>> emptyVector;
        eventCallbacks[eventName] = emptyVector;
        plugin->gameWrapper->UnhookEvent(eventName);
        plugin->gameWrapper->HookEvent(eventName, [this](const std::string &eventName) {
            this->handleEventCallback(eventName);
        });
    }
    eventCallbacks[eventName].push_back(callback);
}

void MultiEventHooker::unhookEvent(BakkesMod::Plugin::BakkesModPlugin *plugin, const std::string &eventName) {
    plugin->gameWrapper->UnhookEvent(eventName);
    eventCallbacks.erase(eventName);
}

void MultiEventHooker::handleEventCallback(const std::string &eventName) {
    std::vector<std::function<void(std::string)>> callbacks = eventCallbacks[eventName];
    for (auto &callback : callbacks) {
        callback(eventName);
    }
}

void MultiEventHooker::hookEventPost(BakkesMod::Plugin::BakkesModPlugin *plugin, const std::string &eventName,
                                 const std::function<void(std::string)> &callback) {
    if (eventPostCallbacks.find(eventName) == eventPostCallbacks.end()) {
        std::vector<std::function<void(std::string)>> emptyVector;
        eventPostCallbacks[eventName] = emptyVector;
        plugin->gameWrapper->UnhookEventPost(eventName);
        plugin->gameWrapper->HookEventPost(eventName, [this](const std::string &eventName) {
            this->handleEventCallback(eventName);
        });
    }
    eventPostCallbacks[eventName].push_back(callback);
}

void MultiEventHooker::unhookEventPost(BakkesMod::Plugin::BakkesModPlugin *plugin, const std::string &eventName) {
    plugin->gameWrapper->UnhookEventPost(eventName);
    eventPostCallbacks.erase(eventName);
}

void MultiEventHooker::handleEventPostCallback(const std::string &eventName) {
    std::vector<std::function<void(std::string)>> callbacks = eventPostCallbacks[eventName];
    for (auto &callback : callbacks) {
        callback(eventName);
    }
}

#pragma once

class PluginComponent
{
public:
    virtual void onEvent(const std::string &eventName, bool post, void *params) = 0;

    virtual void render() = 0;
    virtual void renderCanvas(CanvasWrapper &canvasWrapper) = 0;
};
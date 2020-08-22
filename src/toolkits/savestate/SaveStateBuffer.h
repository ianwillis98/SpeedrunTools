#pragma once

#include <bakkesmod/plugin/bakkesmodplugin.h>
#include <deque>
#include <chrono>
#include "SaveState.h"

using time_point = std::chrono::time_point<std::chrono::system_clock>;
using duration = std::chrono::duration<float>;

class SaveStateBuffer
{
public:
    explicit SaveStateBuffer(std::shared_ptr<float> rewindLength);

    void push(SaveState saveState);

    SaveState front();
    void removeAllButFront();

    int size();
    bool empty();
    void clear();

    void expire();

private:
    std::shared_ptr<float> rewindLength;
    std::deque<std::pair<time_point, SaveState>> buffer;
};

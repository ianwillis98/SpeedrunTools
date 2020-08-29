#pragma once

#include <bakkesmod/plugin/bakkesmodplugin.h>
#include <deque>
#include <chrono>
#include "../../models/GameState.h"

using time_point = std::chrono::time_point<std::chrono::system_clock>;
using duration = std::chrono::duration<float>;

class RewindBuffer
{
private:
    float rewindLength;
    std::deque<std::pair<time_point, GameState>> buffer;

public:
    explicit RewindBuffer(float rewindLength);

    void push(GameState saveState);

    GameState front();
    void removeAllButFront();

    int size();
    bool empty();
    void clear();

    float progress();
    float frontOffset();

    float getRewindLength() const;
    void setRewindLength(float length);

private:
    void expire();
};

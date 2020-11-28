#include <cmath>
#include "RewindBuffer.h"

RewindBuffer::RewindBuffer(float rewindLength) : rewindLength(rewindLength)
{

}

void RewindBuffer::push(GameState saveState)
{
    this->expire();

    auto now = std::chrono::system_clock::now();
    this->buffer.emplace_back(now, saveState);
}

GameState RewindBuffer::front()
{
    this->expire();

    return this->buffer.front().second;
}

void RewindBuffer::removeAllButFront()
{
    this->expire();

    if (this->empty()) return;

    while (this->buffer.size() != 1)
        this->buffer.pop_back();

    this->buffer.front().first = std::chrono::system_clock::now();
}

int RewindBuffer::size()
{
    this->expire();

    return this->buffer.size();
}

bool RewindBuffer::empty()
{
    this->expire();

    return this->buffer.empty();
}

void RewindBuffer::clear()
{
    this->buffer.clear();
}

void RewindBuffer::expire()
{
    time_point now = std::chrono::system_clock::now();
    duration rewindLengthDuration = duration(this->rewindLength);

    while (!this->buffer.empty() && (now - this->buffer.front().first) > rewindLengthDuration)
        this->buffer.pop_front();
}

float RewindBuffer::progress()
{
    this->expire();

    if (this->buffer.empty()) return 0.0f;

    time_point now = std::chrono::system_clock::now();
    duration rewindLengthDuration = duration(this->rewindLength);

    return (now - this->buffer.front().first) / rewindLengthDuration;
}

float RewindBuffer::frontOffset()
{
    this->expire();

    if (this->buffer.empty()) return 0.0f;

    time_point now = std::chrono::system_clock::now();
    duration diff = now - this->buffer.front().first;

    return diff.count();
}

float RewindBuffer::getRewindLength() const
{
    return this->rewindLength;
}

void RewindBuffer::setRewindLength(float length)
{
    this->rewindLength = std::fmax(length, 0.0f);
}
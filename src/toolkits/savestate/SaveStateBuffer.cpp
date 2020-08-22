#include "SaveStateBuffer.h"

SaveStateBuffer::SaveStateBuffer(std::shared_ptr<float> rewindLength)
        : rewindLength(std::move(rewindLength)), buffer()
{

}

void SaveStateBuffer::push(SaveState saveState)
{
    this->expire();

    auto now = std::chrono::system_clock::now();
    this->buffer.emplace_back(now, saveState);
}

SaveState SaveStateBuffer::front()
{
    this->expire();

    return this->buffer.front().second;
}

void SaveStateBuffer::removeAllButFront()
{
    this->expire();

    while (this->buffer.size() != 1)
        this->buffer.pop_back();
}

int SaveStateBuffer::size()
{
    this->expire();

    return this->buffer.size();
}

bool SaveStateBuffer::empty()
{
    this->expire();

    return this->buffer.empty();
}

void SaveStateBuffer::clear()
{
    this->buffer.clear();
}

void SaveStateBuffer::expire()
{
    time_point now = std::chrono::system_clock::now();
    duration rewindLengthDuration = duration(*this->rewindLength);

    while (!this->buffer.empty() && (now - this->buffer.front().first) > rewindLengthDuration)
        this->buffer.pop_front();
}

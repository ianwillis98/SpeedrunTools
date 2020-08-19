#include "SaveStateBuffer.h"

SaveStateBuffer::SaveStateBuffer(int capacity)
{
    this->buffer = std::deque<SaveState>();
    this->capacity = (std::max)(capacity, 1);
}

void SaveStateBuffer::push(SaveState saveState)
{
    if (this->buffer.size() == this->capacity)
        this->buffer.pop_front();

    this->buffer.push_back(saveState);
}

SaveState SaveStateBuffer::getFrontAndRemoveOthers()
{
    if (this->buffer.empty()) return {};

    while (this->buffer.size() != 1)
        this->buffer.pop_back();

    return this->buffer.front();
}

int SaveStateBuffer::getCapacity() const
{
    return this->capacity;
}

void SaveStateBuffer::setCapacity(int c)
{
    this->capacity = (std::max)(capacity, 1);
    while (this->buffer.size() > this->capacity)
        this->buffer.pop_front();
}

int SaveStateBuffer::size() const
{
    return this->buffer.size();
}

bool SaveStateBuffer::empty() const
{
    return this->buffer.empty();
}

#include "SaveStateBuffer.h"

SaveStateBuffer::SaveStateBuffer(int capacity)
{
    this->buffer = std::vector<SaveState>();
    this->capacity = capacity;
    this->head = -1;
}

void SaveStateBuffer::add(SaveState saveState)
{
    this->head++;
    if (this->head == this->capacity)
        this->head = 0;

    if (this->buffer.size() == this->capacity)
    {
        this->buffer.at(this->head) = saveState;
    }
    else
    {
        this->buffer.push_back(saveState);
    }
}

SaveState SaveStateBuffer::getFrontAndRemoveOthers()
{
    if (this->head == -1) return {};

    SaveState front = this->buffer.at(0);
    if (this->buffer.size() == this->capacity)
    {
        int frontIndex = head + 1;
        if (frontIndex == this->capacity)
        {
            frontIndex = 0;
        }
        front = this->buffer.at(frontIndex);
    }

    this->buffer.clear();
    this->buffer.push_back(front);
    this->head = 0;

    return front;
}

bool SaveStateBuffer::isEmpty() const
{
    return head == -1;
}

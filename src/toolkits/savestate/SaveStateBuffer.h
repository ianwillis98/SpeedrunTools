#pragma once

#include <deque>
#include "SaveState.h"

class SaveStateBuffer
{
public:
    explicit SaveStateBuffer(int capacity);

    void push(SaveState saveState);
    SaveState getFrontAndRemoveOthers();

    int getCapacity() const;
    void setCapacity(int c);

    int size() const;
    bool empty() const;

private:
    std::deque<SaveState> buffer;
    int capacity;
};

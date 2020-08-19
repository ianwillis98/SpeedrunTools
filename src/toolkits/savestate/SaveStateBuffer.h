#pragma once

#include <vector>
#include "SaveState.h"


class SaveStateBuffer
{
public:
    explicit SaveStateBuffer(int capacity);

    void add(SaveState saveState);
    SaveState getFrontAndRemoveOthers();
    bool isEmpty() const;

private:
    std::vector<SaveState> buffer;
    int capacity;
    int head;

private:
    class Node
    {
    public:
        SaveState ss;
        Node *next;
    };
};

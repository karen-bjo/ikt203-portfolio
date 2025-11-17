#include "TSongQueue.h"
#include <iostream>

TSongQueue::TSongQueue()
    : front(nullptr), back(nullptr) {}

TSongQueue::~TSongQueue()
{
    clear();
}

void TSongQueue::clear()
{
    Node* current = front;
    while (current != nullptr)
    {
        Node* next = current->next;
        delete current;
        current = next;
    }
    front = nullptr;
    back = nullptr;
}

bool TSongQueue::isEmpty() const
{
    return front == nullptr;
}

void TSongQueue::enqueue(TSong* song)
{
    Node* node = new Node(song, nullptr);

    if (back == nullptr)
    {
        front = node;
        back = node;
    }
    else
    {
        back->next = node;
        back = node;
    }
}

TSong* TSongQueue::dequeue()
{
    if (front == nullptr)
    {
        return nullptr;
    }

    Node* node = front;
    front = front->next;
    if (front == nullptr)
    {
        back = nullptr;
    }

    TSong* song = node->data;
    delete node;
    return song;
}

void TSongQueue::enqueueFront(TSong* song)
{
    Node* node = new Node(song, front);
    front = node;
    if (back == nullptr)
    {
        back = node;
    }
}

void TSongQueue::print() const
{
    Node* current = front;
    int index = 0;

    while (current != nullptr)
    {
        std::cout << index << ": " << current->data->toString() << '\n';
        current = current->next;
        ++index;
    }
}

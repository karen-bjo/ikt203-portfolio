#include "TSongLibraryList.h"
#include <iostream>

TSongLibraryList::TSongLibraryList()
    : head(nullptr), tail(nullptr), count(0)
{
}

TSongLibraryList::~TSongLibraryList()
{
    clear();
}

void TSongLibraryList::clear()
{
    Node* current = head;
    while (current != nullptr)
    {
        Node* next = current->next;
        delete current->data;  // list OWNS the TSong*
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
    count = 0;
}

void TSongLibraryList::append(TSong* song)
{
    Node* node = new Node(song, nullptr, nullptr);

    if (tail == nullptr)
    {
        head = node;
        tail = node;
    }
    else
    {
        node->prev = tail;
        tail->next = node;
        tail = node;
    }

    ++count;
}

TSong* TSongLibraryList::getSongByIndex(int index) const
{
    if (index < 0 || static_cast<std::size_t>(index) >= count)
    {
        return nullptr;
    }

    Node* current = head;
    int i = 0;
    while (current != nullptr && i < index)
    {
        current = current->next;
        ++i;
    }

    return current != nullptr ? current->data : nullptr;
}

std::size_t TSongLibraryList::getCount() const
{
    return count;
}

void TSongLibraryList::printAll() const
{
    Node* current = head;
    int index = 0;

    while (current != nullptr)
    {
        std::cout << index << ": " << current->data->toString() << std::endl;
        current = current->next;
        ++index;
    }
}
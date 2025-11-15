#include "TSongStack.h"
#include <iostream>

TSongStack::TSongStack()
    : top(nullptr)
{
}

TSongStack::~TSongStack()
{
    clear();
}

void TSongStack::clear()
{
    Node* current = top;
    while (current != nullptr)
    {
        Node* next = current->next;
        delete current;    // stack DOES NOT own TSong*, only nodes
        current = next;
    }
    top = nullptr;
}

bool TSongStack::isEmpty() const
{
    return top == nullptr;
}

void TSongStack::push(TSong* song)
{
    Node* node = new Node(song, top);
    top = node;
}

TSong* TSongStack::pop()
{
    if (top == nullptr)
    {
        return nullptr;
    }

    Node* node = top;
    top = top->next;

    TSong* song = node->data;
    delete node;
    return song;
}

void TSongStack::print() const
{
    Node* current = top;
    int index = 0;

    while (current != nullptr)
    {
        std::cout << index << ": " << current->data->toString() << '\n';
        current = current->next;
        ++index;
    }
}
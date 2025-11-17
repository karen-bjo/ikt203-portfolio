#ifndef IKT203_COURSE_ASSIGNMENTS_TSONGSTACK_H
#define IKT203_COURSE_ASSIGNMENTS_TSONGSTACK_H

#include "TSong.h"

class TSongStack
{
public:
    TSongStack();
    ~TSongStack();

    void push(TSong* song);
    TSong* pop();
    bool isEmpty() const;

    void print() const;

    TSongStack(const TSongStack&) = delete;
    TSongStack& operator=(const TSongStack&) = delete;

private:
    class Node
    {
    public:
        TSong* data;
        Node* next;

        Node(TSong* d, Node* n)
            : data(d), next(n) {}
    };

    Node* top;

    void clear();
};

#endif //IKT203_COURSE_ASSIGNMENTS_TSONGSTACK_H
#ifndef IKT203_COURSE_ASSIGNMENTS_TSONGQUEUE_H
#define IKT203_COURSE_ASSIGNMENTS_TSONGQUEUE_H

#include "TSong.h"

class TSongQueue
{
public:
    TSongQueue();
    ~TSongQueue();

    void enqueue(TSong* song);
    TSong* dequeue();
    bool isEmpty() const;

    void enqueueFront(TSong* song);

    void print() const;

    TSongQueue(const TSongQueue&) = delete;
    TSongQueue& operator=(const TSongQueue&) = delete;

private:
    class Node
    {
    public:
        TSong* data;
        Node* next;

        Node(TSong* d, Node* n) : data(d), next(n) {}
    };

    Node* front;
    Node* back;

    void clear();
};

#endif //IKT203_COURSE_ASSIGNMENTS_TSONGQUEUE_H
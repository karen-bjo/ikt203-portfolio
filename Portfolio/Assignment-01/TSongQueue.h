#ifndef IKT203_COURSE_ASSIGNMENTS_TSONGQUEUE_H
#define IKT203_COURSE_ASSIGNMENTS_TSONGQUEUE_H

#include "TSong.h"

//singly linked FIFO queue
class TSongQueue
{
public:
    TSongQueue();
    ~TSongQueue();

    // Standard queue ops
    void   enqueue(TSong* song);   // add at back
    TSong* dequeue();              // remove from front, nullptr if empty
    bool   isEmpty() const;

    // Needed for "play previous": add at front of wish queue
    void   enqueueFront(TSong* song);

    // Extra (beyond assignment): debug / inspection
    void   print() const;

    TSongQueue(const TSongQueue&) = delete;
    TSongQueue& operator=(const TSongQueue&) = delete;

private:
    class Node
    {
    public:
        TSong* data;
        Node*  next;

        Node(TSong* d, Node* n) : data(d), next(n) {}
    };

    Node* front;
    Node* back;

    void clear();
};

#endif //IKT203_COURSE_ASSIGNMENTS_TSONGQUEUE_H
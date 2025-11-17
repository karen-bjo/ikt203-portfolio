#ifndef IKT203_COURSE_ASSIGNMENTS_TSONGLIBRARYLIST_H
#define IKT203_COURSE_ASSIGNMENTS_TSONGLIBRARYLIST_H

#include "TSong.h"
#include <cstddef>

//doubly linked list of TSong*
class TSongLibraryList
{
public:
    TSongLibraryList();
    ~TSongLibraryList();

    // Add song pointer at the end. O(1)
    void append(TSong* song);

    // Access song by index (0..count-1). Returns nullptr if out of range.
    TSong* getSongByIndex(int index) const;

    std::size_t getCount() const;

    // Print all songs in forward order. (Required-ish for UI)
    void printAll() const;

    // Disable copying (avoids double-delete bugs).
    TSongLibraryList(const TSongLibraryList&) = delete;
    TSongLibraryList& operator=(const TSongLibraryList&) = delete;

private:
    class Node
    {
    public:
        TSong* data;
        Node* prev;
        Node* next;

        Node(TSong* d, Node* p, Node* n)
            : data(d), prev(p), next(n) {}
    };

    Node* head;
    Node* tail;
    std::size_t count;

    void clear();
};

#endif //IKT203_COURSE_ASSIGNMENTS_TSONGLIBRARYLIST_H
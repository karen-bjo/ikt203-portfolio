#ifndef IKT203_COURSE_ASSIGNMENTS_TSONGLIBRARYLIST_H
#define IKT203_COURSE_ASSIGNMENTS_TSONGLIBRARYLIST_H

#include "TSong.h"
#include <cstddef>

class TSongLibraryList
{
public:
    TSongLibraryList();
    ~TSongLibraryList();

    void append(TSong* song);

    TSong* getSongByIndex(int index) const;

    std::size_t getCount() const;

    void printAll() const;

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
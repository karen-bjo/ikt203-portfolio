#ifndef IKT203_COURSE_ASSIGNMENTS_TMINHEAP_H
#define IKT203_COURSE_ASSIGNMENTS_TMINHEAP_H

#include <vector>
#include <unordered_map>

class TNode;

class TMinHeap
{
public:
    TMinHeap();

    bool isEmpty() const;

    void insertOrDecrease(TNode *node, int distance);

    bool extractMin(TNode *&outNode, int &outDistance);

private:
    struct THeapItem
    {
        TNode *node;
        int distance;
    };

    std::vector<THeapItem> items;
    std::unordered_map<TNode*, int> nodeIndex;

    void bubbleUp(int index);
    void bubbleDown(int index);
    void swapItems(int first, int second);
};

#endif //IKT203_COURSE_ASSIGNMENTS_TMINHEAP_H
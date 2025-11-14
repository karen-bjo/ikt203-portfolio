#ifndef IKT203_COURSE_ASSIGNMENTS_TMINHEAP_H
#define IKT203_COURSE_ASSIGNMENTS_TMINHEAP_H

#include <vector>
#include <unordered_map>

class TNode;

//min-priority queue storing nodes by their distance value
class TMinHeap
{
public:
    TMinHeap();

    bool isEmpty() const;

    //insert new node or decrease distance if node already exists
    void insertOrDecrease(TNode *node, int distance);

    //extract node with smallest distance; returns false if empty
    bool extractMin(TNode *&outNode, int &outDistance);

private:
    struct THeapItem
    {
        TNode *node;
        int distance;
    };

    std::vector<THeapItem> items;
    std::unordered_map<TNode*, int> nodeIndex; //maps node -> index in items

    void bubbleUp(int index);
    void bubbleDown(int index);
    void swapItems(int first, int second);
};

#endif //IKT203_COURSE_ASSIGNMENTS_TMINHEAP_H
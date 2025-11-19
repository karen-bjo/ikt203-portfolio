#include "TMinHeap.h"

#include "TNode.h"

TMinHeap::TMinHeap() = default;

bool TMinHeap::isEmpty() const
{
    return items.empty();
}

void TMinHeap::insertOrDecrease(TNode *node, int distance)
{
    auto it = nodeIndex.find(node);
    if (it == nodeIndex.end())
    {
        THeapItem item{};
        item.node = node;
        item.distance = distance;

        items.push_back(item);
        int index = static_cast<int>(items.size()) - 1;
        nodeIndex[node] = index;
        bubbleUp(index);
    }
    else
    {
        int index = it->second;
        if (distance < items[index].distance)
        {
            items[index].distance = distance;
            bubbleUp(index);
        }
    }
}

bool TMinHeap::extractMin(TNode *&outNode, int &outDistance)
{
    if (items.empty())
        return false;

    THeapItem root = items.front();
    outNode = root.node;
    outDistance = root.distance;

    nodeIndex.erase(root.node);

    if (items.size() == 1)
    {
        items.clear();
        return true;
    }

    items[0] = items.back();
    nodeIndex[items[0].node] = 0;
    items.pop_back();

    bubbleDown(0);
    return true;
}

void TMinHeap::bubbleUp(int index)
{
    while (index > 0)
    {
        int parentIndex = (index - 1) / 2;
        if (items[index].distance < items[parentIndex].distance)
        {
            swapItems(index, parentIndex);
            index = parentIndex;
        }
        else
        {
            break;
        }
    }
}

void TMinHeap::bubbleDown(int index)
{
    int size = static_cast<int>(items.size());

    while (true)
    {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallest = index;

        if (leftChild < size && items[leftChild].distance < items[smallest].distance)
        {
            smallest = leftChild;
        }

        if (rightChild < size && items[rightChild].distance < items[smallest].distance)
        {
            smallest = rightChild;
        }

        if (smallest != index)
        {
            swapItems(index, smallest);
            index = smallest;
        }
        else
        {
            break;
        }
    }
}

void TMinHeap::swapItems(int first, int second)
{
    THeapItem temp = items[first];
    items[first] = items[second];
    items[second] = temp;

    nodeIndex[items[first].node] = first;
    nodeIndex[items[second].node] = second;
}
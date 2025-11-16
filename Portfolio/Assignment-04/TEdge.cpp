#include "TEdge.h"
#include "TNode.h"

TEdge::TEdge(TNode *from, TNode *to, int weight)
    : fromNode(from), toNode(to), edgeWeight(weight) {}

TNode *TEdge::getFrom() const
{
    return fromNode;
}

TNode *TEdge::getTo() const
{
    return toNode;
}

int TEdge::getWeight() const
{
    return edgeWeight;
}
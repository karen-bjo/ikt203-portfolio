#include "TNode.h"
#include "TEdge.h"

TNode::TNode(const std::string &name)
    : nodeName(name)
{
}

const std::string &TNode::getName() const
{
    return nodeName;
}

void TNode::addEdge(TEdge *edge)
{
    edges.push_back(edge);
}

const std::vector<TEdge*> &TNode::getEdges() const
{
    return edges;
}


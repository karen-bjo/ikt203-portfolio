#include "TGraph.h"
#include "TNode.h"
#include "TEdge.h"

TGraph::TGraph() = default;

TGraph::~TGraph()
{
    deleteAllEdges();
    deleteAllNodes();
}

void TGraph::deleteAllEdges()
{
    for (TEdge *edge : edges)
    {
        delete edge;
    }
    edges.clear();
}

void TGraph::deleteAllNodes()
{
    for (TNode *node : nodes)
    {
        delete node;
    }
    nodes.clear();
}

TNode *TGraph::findNode(const std::string &name) const
{
    for (TNode *node : nodes)
    {
        if (node->getName() == name)
        {
            return node;
        }
    }
    return nullptr;
}

TNode *TGraph::getOrCreateNode(const std::string &name)
{
    TNode *existing = findNode(name);
    if (existing != nullptr)
    {
        return existing;
    }

    TNode *newNode = new TNode(name);
    nodes.push_back(newNode);
    return newNode;
}

void TGraph::addUndirectedEdge(const std::string &fromName,
                               const std::string &toName,
                               int weight)
{
    TNode *fromNode = getOrCreateNode(fromName);
    TNode *toNode = getOrCreateNode(toName);

    //edge from -> to
    TEdge *edge1 = new TEdge(fromNode, toNode, weight);
    edges.push_back(edge1);
    fromNode->addEdge(edge1);

    //edge to -> from (because graph is undirected)
    TEdge *edge2 = new TEdge(toNode, fromNode, weight);
    edges.push_back(edge2);
    toNode->addEdge(edge2);
}

const std::vector<TNode*> &TGraph::getNodes() const
{
    return nodes;
}
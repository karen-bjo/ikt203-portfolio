#include "TDijkstra.h"

#include "TGraph.h"
#include "TNode.h"
#include "TEdge.h"
#include "TMinHeap.h"

#include <unordered_map>
#include <unordered_set>
#include <limits>

TDijkstra::TDijkstra(TGraph &graphRef)
    : graph(graphRef)
{
}

bool TDijkstra::findShortestPath(const std::string &sourceName,
                                 const std::string &destinationName,
                                 std::vector<TNode*> &outPath,
                                 int &outTotalCost)
{
    outPath.clear();
    outTotalCost = 0;

    TNode *sourceNode = graph.findNode(sourceName);
    TNode *destinationNode = graph.findNode(destinationName);

    if (sourceNode == nullptr || destinationNode == nullptr)
    {
        return false;
    }

    const int INF = std::numeric_limits<int>::max();

    std::unordered_map<TNode*, int> distance;
    std::unordered_map<TNode*, TNode*> previous;
    std::unordered_set<TNode*> visited;

    TMinHeap heap;

    //initialize all distances to INF
    const std::vector<TNode*> &nodes = graph.getNodes();
    for (TNode *node : nodes)
    {
        distance[node] = INF;
    }

    distance[sourceNode] = 0;
    heap.insertOrDecrease(sourceNode, 0);

    while (!heap.isEmpty())
    {
        TNode *currentNode = nullptr;
        int currentDistance = 0;
        if (!heap.extractMin(currentNode, currentDistance))
        {
            break;
        }

        if (visited.find(currentNode) != visited.end())
        {
            continue;
        }
        visited.insert(currentNode);

        if (currentNode == destinationNode)
        {
            break;
        }

        const std::vector<TEdge*> &edges = currentNode->getEdges();
        for (TEdge *edge : edges)
        {
            TNode *neighbor = edge->getTo();
            if (visited.find(neighbor) != visited.end())
            {
                continue;
            }

            int newDistance = currentDistance + edge->getWeight();
            auto it = distance.find(neighbor);
            int oldDistance = (it != distance.end()) ? it->second : INF;

            if (newDistance < oldDistance)
            {
                distance[neighbor] = newDistance;
                previous[neighbor] = currentNode;
                heap.insertOrDecrease(neighbor, newDistance);
            }
        }
    }

    if (distance[destinationNode] == INF)
    {
        return false; //no path
    }

    //reconstruct path backwards from destination
    TNode *current = destinationNode;
    while (current != nullptr)
    {
        outPath.insert(outPath.begin(), current);
        auto itPrev = previous.find(current);
        if (itPrev == previous.end())
        {
            break;
        }
        current = itPrev->second;
    }

    outTotalCost = distance[destinationNode];
    return true;
}
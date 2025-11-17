#include "option1.h"

#include "TDijkstra.h"
#include <vector>

#include <iostream>
#include <string>

#include "DataPath.h"
#include "TGraph.h"
#include "TNode.h"
#include "SharedLib.h"    // declares readGraphFromFile, FNodeRead, FEdgeRead

//global pointer to the graph used while reading the file
static TGraph *gCurrentGraph = nullptr;

//callback for each node line in the file
static bool OnNodeRead(int index, int total, const std::string &nodeName)
{
	if (gCurrentGraph == nullptr)
	{
		return false;
	}

	gCurrentGraph->getOrCreateNode(nodeName);
	return true;
}

//callback for each edge line in the file
static bool OnEdgeRead(int index, int total, const std::string &fromNode, const std::string &toNode, float weight)
{
	if (gCurrentGraph == nullptr)
	{
		return false;
	}

	//our graph uses int weights, file uses float -> cast
	gCurrentGraph->addUndirectedEdge(fromNode, toNode, static_cast<int>(weight));
	return true;
}

int RunApp()
{
	TGraph graph;
	gCurrentGraph = &graph;

	std::string filePath = GetDataPath("network_graph.txt");
	std::cout << "Loading graph from: " << filePath << std::endl;

	//readGraphFromFile is implemented in ReadGraph.cpp, declared in SharedLib.h
	readGraphFromFile(filePath, OnNodeRead, OnEdgeRead);

	std::cout << "Nodes loaded from graph:" << std::endl;
	for (TNode *node : graph.getNodes())
	{
		std::cout << "- " << node->getName() << std::endl;
	}
	std::cout << std::endl;

	std::string sourceName;
	std::string destinationName;

	std::cout << "Enter source server name: ";
	std::getline(std::cin >> std::ws, sourceName);

	std::cout << "Enter destination server name: ";
	std::getline(std::cin, destinationName);

	TDijkstra dijkstra(graph);
	std::vector<TNode*> path;
	int totalCost = 0;

	if (dijkstra.findShortestPath(sourceName, destinationName, path, totalCost))
	{
		std::cout << "Shortest path: ";
		for (std::size_t i = 0; i < path.size(); ++i)
		{
			std::cout << path[i]->getName();
			if (i + 1 < path.size())
			{
				std::cout << " -> ";
			}
		}
		std::cout << std::endl;
		std::cout << "Total latency: " << totalCost << std::endl;
	}
	else
	{
		std::cout << "No path found, or one of the server names was invalid." << std::endl;
	}


	gCurrentGraph = nullptr;
	return 0;
}
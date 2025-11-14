#ifndef IKT203_COURSE_ASSIGNMENTS_TDIJKSTRA_H
#define IKT203_COURSE_ASSIGNMENTS_TDIJKSTRA_H

#include <string>
#include <vector>

class TGraph;
class TNode;

//runs Dijkstra's algorithm on a TGraph
class TDijkstra
{
public:
    explicit TDijkstra(TGraph &graph);

    //returns true if a path exists, false otherwise
    bool findShortestPath(const std::string &sourceName,
                          const std::string &destinationName,
                          std::vector<TNode*> &outPath,
                          int &outTotalCost);

private:
    TGraph &graph;
};

#endif //IKT203_COURSE_ASSIGNMENTS_TDIJKSTRA_H
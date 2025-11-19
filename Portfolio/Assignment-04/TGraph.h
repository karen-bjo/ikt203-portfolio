#ifndef IKT203_COURSE_ASSIGNMENTS_TGRAPH_H
#define IKT203_COURSE_ASSIGNMENTS_TGRAPH_H

#include <string>
#include <vector>

class TNode;
class TEdge;

class TGraph
{
public:
    TGraph();
    ~TGraph();

    TNode *getOrCreateNode(const std::string &name);
    TNode *findNode(const std::string &name) const;

    void addUndirectedEdge(const std::string &fromName, const std::string &toName, int weight);

    const std::vector<TNode*> &getNodes() const;

private:
    std::vector<TNode*> nodes;
    std::vector<TEdge*> edges;

    void deleteAllEdges();
    void deleteAllNodes();
};

#endif //IKT203_COURSE_ASSIGNMENTS_TGRAPH_H
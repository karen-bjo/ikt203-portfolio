#ifndef IKT203_COURSE_ASSIGNMENTS_TGRAPH_H
#define IKT203_COURSE_ASSIGNMENTS_TGRAPH_H

#include <string>
#include <vector>

class TNode;
class TEdge;

//owns all nodes and edges (responsible for delete)
class TGraph
{
public:
    TGraph();
    ~TGraph();

    //creates node if it does not exist, otherwise returns existing one
    TNode *getOrCreateNode(const std::string &name);
    TNode *findNode(const std::string &name) const;

    //adds an undirected edge (both directions)
    void addUndirectedEdge(const std::string &fromName,
                           const std::string &toName,
                           int weight);

    const std::vector<TNode*> &getNodes() const;

private:
    std::vector<TNode*> nodes;
    std::vector<TEdge*> edges; //all edges owned here

    void deleteAllEdges();
    void deleteAllNodes();
};

#endif //IKT203_COURSE_ASSIGNMENTS_TGRAPH_H
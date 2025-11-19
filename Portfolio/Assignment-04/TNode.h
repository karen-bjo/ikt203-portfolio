#ifndef IKT203_COURSE_ASSIGNMENTS_TNODE_H
#define IKT203_COURSE_ASSIGNMENTS_TNODE_H

#include <string>
#include <vector>

class TEdge;

class TNode
{
public:
    explicit TNode(const std::string &name);

    const std::string &getName() const;
    void addEdge(TEdge *edge);

    const std::vector<TEdge*> &getEdges() const;

private:
    std::string nodeName;
    std::vector<TEdge*> edges;
};

#endif //IKT203_COURSE_ASSIGNMENTS_TNODE_H
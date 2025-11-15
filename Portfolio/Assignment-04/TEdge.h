#ifndef IKT203_COURSE_ASSIGNMENTS_TEDGE_H
#define IKT203_COURSE_ASSIGNMENTS_TEDGE_H

class TNode;

//represents a weighted connection between two nodes
class TEdge
{
public:
    TEdge(TNode *from, TNode *to, int weight);

    TNode *getFrom() const;
    TNode *getTo() const;
    int getWeight() const;

private:
    TNode *fromNode; //non-owning
    TNode *toNode;   //non-owning
    int edgeWeight;
};

#endif //IKT203_COURSE_ASSIGNMENTS_TEDGE_H
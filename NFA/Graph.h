//
// Created by Manfi on 05/03/21.
//

#ifndef PROJECT_GRAPH_H
#define PROJECT_GRAPH_H

#include "Node.h"
#include <queue>

class Graph {
private:
    Node* start;
    Node* end;
public:
    static const char LAMBDA = '?';
    Graph(char name) {
        start = new Node;
        end = new Node;
        start->add_edge(new Edge(end, name));
    }
    Node* get_start();
    Node* get_end();
    void union_with(Graph* graph);
    void concatenate_with(Graph* graph);
    void kleene_closure();
    void print();
};


#endif //PROJECT_GRAPH_H

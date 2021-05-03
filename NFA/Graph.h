//
// Created by Manfi on 05/03/21.
//

#ifndef PROJECT_GRAPH_H
#define PROJECT_GRAPH_H

#include "Edge.h"
#include "Node.h"

class Graph {
private:
    Node* start;
    Node* end;
public:
    static const char EPS = 'e';
    Graph() {
        Graph(EPS);
    }
    Graph(char name) {
        start = new Node;
        end = new Node;
        start->add_edge(new Edge(end, name));
    }
    Node* get_start();
    Node* get_end();
    void union_with(Graph* graph);
    void concatenate_with(Graph* graph);
    void Kleene_closure();
};


#endif //PROJECT_GRAPH_H

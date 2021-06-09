//
// Created by Manfi on 05/03/21.
//

#ifndef PROJECT_GRAPH_H
#define PROJECT_GRAPH_H

#include "Node.h"
#include <queue>
#include <unordered_set>

class Graph {
private:
    Node* start;
    Node* end;

public:
    static const char LAMBDA = '?';

    Graph(char name);

    ~Graph(){}

    Node* get_start();

    Node* get_end();

    void union_with(Graph* graph);

    void concatenate_with(Graph* graph);

    void kleene_closure();

    static void print(Node* root);

    static void delete_graph(Graph* graph);
};


#endif //PROJECT_GRAPH_H

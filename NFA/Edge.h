//
// Created by Manfi on 05/03/21.
//
#ifndef PROJECT_EDGE_H
#define PROJECT_EDGE_H

#include "Node.h"

class Node ;

class Edge {
private:
    Node* node;
    const char name;

public:
    Edge(Node* node, char name): node(node), name(name){};

    ~Edge(){};

    Node* get_node();

    char get_name();
};


#endif //PROJECT_EDGE_H

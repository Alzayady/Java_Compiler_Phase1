//
// Created by Manfi on 05/03/21.
//

#ifndef PROJECT_NODE_H
#define PROJECT_NODE_H

#include <iostream>
#include <vector>
#include "Edge.h"

class Node {
private:
    static unsigned int cnt = 0;
    int id;
    std::string expression_name;

    std::vector<Edge*> edges;

public:
    Node() {
        id = ++cnt;
    }
    void add_edge(Edge* edge);
    void set_expression_name (std::string name);
    std::string get_expression_name();
    bool is_accepted();
    int get_id();
};


#endif //PROJECT_NODE_H

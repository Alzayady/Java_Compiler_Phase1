//
// Created by Manfi on 05/03/21.
//

#ifndef PROJECT_NODE_H
#define PROJECT_NODE_H

#include <iostream>
#include <vector>

class Edge;

class Node {
private:
    static unsigned int cnt;
    int id;
    std::string expression_name;

    std::vector<Edge*> edges;

public:
    Node() {
        id = cnt++;
    }
    void add_edge(Edge* edge);
    std::vector<Edge*> get_edges();
    void set_expression_name (std::string name);
    std::string get_expression_name();
    bool is_accepted();
    int get_id();
};


#endif //PROJECT_NODE_H

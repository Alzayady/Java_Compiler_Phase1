//
// Created by Manfi on 05/03/21.
//

#include "NFA_Generator.h"

void NFA_Generator::add_expression(std::string name, std::string expression) {

}

Node * NFA_Generator::combine() {
    Node* root = new Node;
    for(Graph* expression: expressions) {
        root->add_edge(new Edge(expression->get_start(), Graph::LAMBDA));
    }
    return root;
}

void NFA_Generator::go() {
    Node* root = combine();
    // call hamza method;
}
//
// Created by Manfi on 05/03/21.
//

#include "Node.h"

#include <utility>

void Node::add_edge(Edge* edge) {
    edges.push_back(edge);
}

bool Node::is_accepted() {
    return not expression_name.empty() or edges.empty();
}

int Node::get_id() {
    return id;
}

void Node::set_expression_name(std::string name) {
    this->expression_name = std::move(name);
}

std::string Node::get_expression_name() {
    return expression_name;
}

std::vector<Edge*> Node::get_edges() {
    return edges;
}

//
// Created by Manfi on 05/03/21.
//

#include "Node.h"

unsigned int Node::cnt = 0;

void Node::add_edge(Edge *edge) {
    edges.push_back(edge);
}

bool Node::is_accepted() {
    return not expression_name.empty() or edges.empty();
}

int Node::get_id() {
    return id;
}

void Node::set_expression_name(std::string name) {
    this->expression_name = name;
}

std::string Node::get_expression_name() {
    return expression_name;
}

bool Node::operator<(const Node &other) const {
    return (this->id) < (other.id);
}

std::vector<Edge *> Node::get_edges() {
    return edges;
}

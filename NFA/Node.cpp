//
// Created by Manfi on 05/03/21.
//

#include "Node.h"
#include <unordered_set>

unsigned int Node::cnt = 0;

Node::Node() {
    id = ++cnt;
}

Node::~Node() {
    for (Edge *edge: edges) {
        delete edge;
    }
}

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

std::vector<Edge *> Node::get_edges() {
    return edges;
}

void dfs(Node *node, std::unordered_set<Node *> &vis) {
    vis.insert(node);
    for (Edge *edge: node->get_edges()) {
#ifdef __DEBUGMODE
        std::cout << "trying to go to node " << edge->get_node()->get_id() << std::endl;
#endif
        if (!vis.count(edge->get_node())) {
#ifdef __DEBUGMODE
            std::cout << "went  to go to node " << edge->get_node()->get_id() << std::endl;
#endif
            dfs(edge->get_node(), vis);
        } else {
#ifdef __DEBUGMODE
            std::cout << "failed to go to node " << edge->get_node()->get_id() << std::endl;
#endif
        }
    }
#ifdef __DEBUGMODE
    std::cout << "hello" << node->get_id() << std::endl;
#endif

    delete node;
}

void Node::delete_node_cascade(Node *node) {
    std::unordered_set<Node *> vis;
    dfs(node, vis);
#ifdef __DEBUGMODE
    std::cout << "Finished deleting the graph nodes successfully " << std::endl;
#endif
}

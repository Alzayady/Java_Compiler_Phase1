#include <iostream>
#include "NFA/Graph.h"
#include "NFA/Edge.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Node* node = new Node;
    std::cout << node->get_id() << std::endl;
    std::cout << node->is_accepted() << std::endl;
    Edge* edge = new Edge(node, Graph::LAMBDA);
    std::cout << edge->get_node()->get_id() << std::endl;
    node->add_edge(new Edge(node, Graph::LAMBDA));
    std::cout<< node->get_edges().front()->get_name() << std::endl;
    return 0;
}

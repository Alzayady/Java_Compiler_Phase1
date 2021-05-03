#include <iostream>
#include "NFA/Graph.h"
#include "NFA/NFA_Generator.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::string input = "(w&h&i&l&e)";
    NFA_Generator* nfaGenerator = new NFA_Generator;
    Graph* graph = nfaGenerator->to_NFA(input);
    graph->print();
    return 0;
}

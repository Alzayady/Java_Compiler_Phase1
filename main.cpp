#include <iostream>
#include "NFA/Graph.h"
#include "NFA/NFA_Generator.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::string input = "0&1|0&0";
    NFA_Generator* nfaGenerator = new NFA_Generator;
    Graph* graph = nfaGenerator->to_NFA(input);
    graph->print();
    return 0;
}

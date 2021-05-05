#include <iostream>
#include "NFA/Graph.h"
#include "NFA/NFA_Generator.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::string input = "w&h&i&l&e";
    NFA_Generator* nfaGenerator = new NFA_Generator;
    nfaGenerator->add_expression("while",input);
    input = "\\(";
    nfaGenerator->add_expression("\\(",input);
    input = "\\)";
    nfaGenerator->add_expression("\\)",input);
    input = ";";
    nfaGenerator->add_expression(";",input);
    nfaGenerator->go();

    return 0;
}

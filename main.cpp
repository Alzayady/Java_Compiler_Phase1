#include <iostream>
#include "NFA/Graph.h"
#include "NFA/NFA_Generator.h"
#include "LexicalAnalyzer.h"
int main() {
<<<<<<< HEAD
    freopen("../out.txt","w",stdout);
=======
    freopen("../out.txt", "w", stdout);
>>>>>>> c43a596346a742c54a93fdc9648560c044feef0c
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

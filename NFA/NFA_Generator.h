//
// Created by Manfi on 05/03/21.
//

#ifndef PROJECT_NFA_GENERATOR_H
#define PROJECT_NFA_GENERATOR_H

#include <iostream>
#include <vector>
#include "../DFA/GraphAdapter.h"
#include "Graph.h"
#include "Node.h"

class NFA_Generator {
private:
    std::vector<Graph*> expressions;
public:
    void add_expression(std::string name, std::string& expression);
    LexicalAnalyzer* go();
    Graph* to_NFA(std::string& expression);
    Node* combine();
};


#endif //PROJECT_NFA_GENERATOR_H

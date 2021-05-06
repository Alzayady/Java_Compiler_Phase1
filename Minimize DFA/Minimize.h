//
// Created by HP-SYSTEMS on 5/4/2021.
//

#ifndef JAVA_COMPILER_MINIMIZE_H
#define JAVA_COMPILER_MINIMIZE_H


#include <vector>
#include "Table.h"

class Minimize {
private:
    std::vector<State *> graph;
public:
    Minimize(std::vector<State *> graph, Node * root);
    Table * run();
    int id_root;
};


#endif //JAVA_COMPILER_MINIMIZE_H

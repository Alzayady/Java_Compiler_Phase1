//
// Created by HP-SYSTEMS on 5/4/2021.
//

#ifndef JAVA_COMPILER_MINIMIZE_H
#define JAVA_COMPILER_MINIMIZE_H

#include "../DFA/ResultState.h"

#include <vector>
#include "Table.h"
#include <iostream>

class Minimize {
private:
    std::vector<ResultState *> *graph;
public:
    Minimize(std::vector<ResultState *> *graph, int id_root);
    Table * run();
    int id_root;
};


#endif //JAVA_COMPILER_MINIMIZE_H

//
// Created by KING on 5/6/2021.
//

#ifndef JAVA_COMPILER_GRAPHADAPTER_H
#define JAVA_COMPILER_GRAPHADAPTER_H


#include "../NFA/Node.h"
#include "../analyze_to_tokens/LexicalAnalyzer.h"

class GraphAdapter {
public:
    GraphAdapter() ;
    LexicalAnalyzer* get_lexical_analyzer(Node *root);
};


#endif //JAVA_COMPILER_GRAPHADAPTER_H

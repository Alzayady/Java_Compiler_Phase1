//
// Created by HP-SYSTEMS on 5/5/2021.
//

#ifndef JAVA_COMPILER_LEXICALANALYZER_H
#define JAVA_COMPILER_LEXICALANALYZER_H


#include "../Minimize DFA/Table.h"
#include "Token.h"

class LexicalAnalyzer {
private:
    Table * table ;
public:
    LexicalAnalyzer(Table *table);
    std::vector<Token *> convert(std::string);

};


#endif //JAVA_COMPILER_LEXICALANALYZER_H

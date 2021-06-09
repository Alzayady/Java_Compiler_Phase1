//
// Created by KING on 5/7/2021.
//

#ifndef JAVA_COMPILER_RESULTSTATE_H
#define JAVA_COMPILER_RESULTSTATE_H
#include <string>
#include <unordered_map>
#include <cassert>
#include <sstream>


class ResultState{
    int id ;
    std::string expression_name ;
    std::unordered_map<char , ResultState*> transitions ;
    bool accepted  ;

public:
    ResultState(int id);
    bool is_accepted() ;
    int get_id() ;
    std::string get_expression_name() ;
    std::unordered_map<char , ResultState*> get_transitions() ;

    void set_expression_name(std::string name ) ;
    void add_transition(char c , ResultState* nxt) ;
    void set_as_accepted() ;
    std::string to_string() ;
};



#endif //JAVA_COMPILER_RESULTSTATE_H


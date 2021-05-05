//
// Created by HP-SYSTEMS on 5/4/2021.
//

#ifndef JAVA_COMPILER_ROW_H
#define JAVA_COMPILER_ROW_H


#include <vector>

#include "Table.h"
class Table ;
class Row {
private:
    int rowNumber;
    std::vector<State *> states;
    Table *table;
    bool accepted;
    std::string name; // in case of accepting state
    std::vector <std::vector<int>> cell_vector; // for every row , for every input , it contains the next row numbers , it may
    // contain more than next state during running , but at the end it will contain
    // only one next state , and ربنا يستر وتطلع صح
public:
    Row(int rowNumber);

    int getRowNumber();

    bool needSplit();


    void set_table(Table *table);

    void set_status(std::vector<State *> states) ;

    bool isAccepted();

    std::string get_expression_name();

    void set_accepted(std::string name);

    std::vector<State *> get_status();

    void init();

    void split();

    bool has_same_transition(State *state1, State *state2) ;

    int get_next_row_under_input(int input, State *st);


    int get_next_row(int input);

    std::string toString();


};


#endif //JAVA_COMPILER_ROW_H

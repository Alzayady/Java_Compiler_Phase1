//
// Created by HP-SYSTEMS on 5/4/2021.
//

#ifndef JAVA_COMPILER_TABLE_H
#define JAVA_COMPILER_TABLE_H


#include <vector>
#include <unordered_set>
#include <map>
#include "../DFA/State.h"

class Row;
class Table {
private:
    std::vector<char>inputs;
    std::vector<Row *>Rows;
    std::unordered_map<int , int> idToRow;
    int ID = 0 ;
public:
    Table(std::unordered_set<char>inputs);
    Row *  add_row(std::vector<State *> states);
    std::vector<char>get_inputs();
    void init();
    void update_map_converting_id_to_row();
    int convert_id_to_row(int i);
    int input_to_column(char input);
    std::string toString();
    void init_all_rows();
};


#endif //JAVA_COMPILER_TABLE_H

//
// Created by HP-SYSTEMS on 5/4/2021.
//

#ifndef JAVA_COMPILER_TABLE_H
#define JAVA_COMPILER_TABLE_H


#include <vector>
#include <unordered_set>
#include <map>
#include "../DFA/ResultState.h"

class Row;

class Table {
private:
    std::vector<char> inputs;
    std::vector<Row *> Rows;
    std::unordered_map<int, int> idToRow;
    int ID = 0;
    int root_id;
    int start_row;

    int input_to_column(char input);

public:
    Table(std::unordered_set<char> inputs, int i);

    Row *add_row(std::vector<ResultState *> states);

    std::vector<char> get_inputs();

    void init();

    void update_map_converting_id_to_row();

    int convert_id_to_row(int i);

    std::string toString();

    void init_all_rows();

    int get_start_row();

    int next_row(char input, int cur_row);

    bool can_go(int row, char input);

    bool isAcceptedRow(int row);

    std::string getAcceptedName(int row);

    void make_stable();
};


#endif //JAVA_COMPILER_TABLE_H

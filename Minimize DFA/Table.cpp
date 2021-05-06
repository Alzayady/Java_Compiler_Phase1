//
// Created by HP-SYSTEMS on 5/4/2021.
//

#include <algorithm>
#include <cassert>
#include "Table.h"
#include "Row.h"
#include "Row.cpp"

Table::Table(std::unordered_set<char> inputs, int root_id) {
    for (char it : inputs) {
        this->inputs.push_back(it);
    }
    std::sort(this->inputs.begin(), this->inputs.end());
    this->root_id = root_id;
}

void Table::init() {
    this->update_map_converting_id_to_row();
    this->init_all_rows();
    bool need_split = true;
    while (need_split) {
        this->start_row = idToRow[this->root_id];
        std::cout << toString() << std::endl;
        need_split = false;
        for (Row *row : this->Rows) {
            if (row->needSplit()) {
                row->split();
                need_split = true;
                this->update_map_converting_id_to_row();
                this->init_all_rows();
                break;
            }
        }
    }
    this->start_row = idToRow[this->root_id];
}


Row *Table::add_row(std::vector<State *> states) {
    if (states[0]->is_accepted()) {
        for (State *st : states) {
            assert(st->get_accepted_node()->get_expression_name() ==
                   states[0]->get_accepted_node()->get_expression_name());
        }
    }
    Row *row = new Row(this->ID++);
    row->set_table(this);
    row->set_status(states);
    if (states[0]->is_accepted()) {
        row->set_accepted(states[0]->get_accepted_node()->get_expression_name());
    }
    this->Rows.push_back(row);
    return row;
}

std::vector<char> Table::get_inputs() {
    return this->inputs;
}

void Table::update_map_converting_id_to_row() {
    idToRow.clear();
    for (Row *row : this->Rows) {
        for (State *st : row->get_status()) {
            for (Node *node : *st->get_state_nodes()) {
                idToRow[node->get_id()] = row->getRowNumber();
            }
        }

    }
}

void Table::init_all_rows() {
    for (Row *row : this->Rows) {
        row->init();
    }
}

int Table::convert_id_to_row(int input) {
    assert(this->idToRow.count(input));
    return idToRow[input];
}

int Table::input_to_column(char input) {
    for (int i = 0; i < inputs.size(); i++) {
        if (inputs[i] == input) {
            return i;
        }
    }
    return -1;
}

std::string Table::toString() {
    std::string ans = "inputs | random node id "; // 20 char
    for (auto it :inputs) {
        ans += "|          ";
        ans += it;
        ans += "        ";

    }

    ans += "\n";
    ans+=std::string(ans.size(),'_');
    ans+="\n";
    for (auto it: Rows) {
        ans += it->toString();
        ans += "\n";
    }
    return ans;
}

int Table::get_start_row() {
    return this->start_row;
}

int Table::next_row(char input, int cur_row) {
    int column = input_to_column(input);
    return this->Rows[cur_row]->get_next_row(column);
}

bool Table::can_go(int row, char input) {
    return this->next_row(input, row) != -1;
}

bool Table::isAcceptedRow(int row) {
    return this->Rows[row]->isAccepted();
}

std::string Table::getAcceptedName(int row) {
    assert(Rows[row]->isAccepted());
    return Rows[row]->get_expression_name();
}


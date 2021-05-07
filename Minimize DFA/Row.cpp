//
// Created by HP-SYSTEMS on 5/4/2021.
//

#include <cassert>
#include <sstream>
#include "Row.h"
#include "../DFA/ResultState.h"
#include "../DFA/ResultState.cpp"


Row::Row(int rowNumber) {
    this->rowNumber = rowNumber;
    this->accepted = false;
}

void Row::set_table(Table *table) {
    this->table = table;
}

void Row::set_status(std::vector<ResultState *> states) {
    this->states = states;
}

void Row::set_accepted(std::string name) {
    this->accepted = true;
    this->name = name;
}

std::string Row::get_expression_name() {
    return this->name;
}

bool Row::isAccepted() {
    return this->accepted;
}

int Row::getRowNumber() {
    return this->rowNumber;
}

std::vector<ResultState *> Row::get_status() {
    return this->states;
}

void Row::init() {
    std::vector<char> inputs = this->table->get_inputs();
    this->cell_vector.clear();
    this->cell_vector.resize(inputs.size());
    for (int i = 0; i < inputs.size(); i++) {
        std::unordered_set<int> hashed_next;
        for (ResultState *st: this->get_status()) {
            int next_row = this->get_next_row_under_input(inputs[i], st);
            if (hashed_next.count(next_row))continue;
            hashed_next.insert(next_row);
            this->cell_vector[i].push_back(next_row);
        }
    }

}

void Row::split() {
    std::vector<ResultState *> states_row1, states_row2;
    states_row1.push_back(this->states[0]);
    for (int i = 1; i < states.size(); i++) {
        if (this->has_same_transition(this->states[0], this->states[i])) {
            states_row1.push_back(this->states[i]);
        } else {
            states_row2.push_back(this->states[i]);
        }
    }
    assert(!states_row2.empty());
    this->states = states_row1;
    this->table->add_row(states_row2);

}

bool Row::needSplit() {
    for (int i = 0; i < this->table->get_inputs().size(); i++) {
        if (this->cell_vector[i].size() > 1) {
            return true;
        }
    }
    return false;
}

bool Row::has_same_transition(ResultState *state1, ResultState *state2) {
    for (char input : this->table->get_inputs()) {
        int next1 = this->get_next_row_under_input(input, state1);
        int next2 = this->get_next_row_under_input(input, state2);
        if (next1 != next2)return false;
    }
    return true;
}

int Row::get_next_row_under_input(int input, ResultState *st) {
    std::unordered_map<char, ResultState *> trans = st->get_transitions();
    if (trans.count(input)) {
        int next_row = this->table->convert_id_to_row(trans[input]->get_id());
        return next_row;
    }
    return -1;
}


int Row::get_next_row(int column) {
    if (column == -1) {
        return -1;
    }
    assert(cell_vector[column].size() == 1);
    return cell_vector[column][0];
}

std::string Row::toString() {
    std::string str;
    str += char(this->getRowNumber() + '0');
    if (this->table->get_start_row() == this->getRowNumber()) {
        str += " ) <--|";
    } else {
        str += " )    |";
    }
    int dif = 11 - str.size();
    while (dif >= 0) {
        dif--;
        str += " ";
    }
    for (ResultState *it : states) {
        int n = it->get_id();
        std::stringstream ss;
        ss << n;
        std::string temp = ss.str();
        str += temp;
        break;
    }
    int sp = 23 - str.size();
    while (sp > 0) {
        str += " ";
        sp--;
    }
    for (auto it :this->cell_vector) {
        std::string temp;
        temp += " |  ";
        for (auto itt : it) {
            if (itt == -1) {
                temp += " -1 ,";
                continue;
            }
            temp += "  ";
            temp += char(itt + '0');
            temp += " , ";
        }
        temp.pop_back();
        temp.pop_back();
        sp = 20 - temp.size();
        while (sp--) {
            temp += " ";
        }
        str += temp;
    }
    if (this->isAccepted()) {
        str += "  Accepted name :  " + this->get_expression_name();
    }
    return str;

}

void Row::make_stable() {
     for(ResultState * resultState : states){
         delete resultState;
     }
}








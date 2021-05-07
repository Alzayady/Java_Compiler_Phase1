//
// Created by HP-SYSTEMS on 5/4/2021.
//

#include <iostream>
#include "Minimize.h"
#include "Table.h"
#include "Table.cpp"

using namespace std;

Minimize::Minimize(std::vector<ResultState *> *graph, int id_root) {

    this->graph = graph;
    this->id_root = id_root;
//    cout << " ======================== " << endl;
//    cout << id_root << endl;
//    for (auto it : *graph) {
//        if (it->is_accepted()) {
//            cout << it->get_id() << endl;
//            cout << it->get_expression_name() << endl;
//        }
//    }
}

Table *Minimize::run() {
    std::map<std::string, std::vector<ResultState *> > accepted_states;
    std::vector<ResultState *> not_accepted_stats;

    std::unordered_set<char> inputs;

    for (ResultState *st : *graph) {

        if (!st->is_accepted()) {
            not_accepted_stats.push_back(st);
        } else {
            accepted_states[st->get_expression_name()].push_back(st);
        }

    }

    for (ResultState *st :*graph) {
        for (auto it  : st->get_transitions()) {
            inputs.insert(it.first);
        }
    }
    std::vector<std::vector<ResultState * >> rows;
    Table *table = new Table(inputs, this->id_root);
    for (auto it : accepted_states) {
        table->add_row(it.second);
    }
    if (!not_accepted_stats.empty())
        table->add_row(not_accepted_stats);
    table->init();
    table->make_stable();
    return table;
}
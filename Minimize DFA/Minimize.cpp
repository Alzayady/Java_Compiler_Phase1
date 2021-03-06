//
// Created by HP-SYSTEMS on 5/4/2021.
//

#include "Minimize.h"
#include "Table.h"

Minimize::Minimize(std::vector<State *> graph) {
    this->graph = graph;
}

Table *Minimize::run() {
    std::map<std::string, std::vector<State *> > accepted_states;
    std::vector<State *> not_accepted_stats;

    std::unordered_set<char> inputs;

    for (State *st : graph) {

        if (!st->is_accepted()) {
            not_accepted_stats.push_back(st);
        } else {
            accepted_states[st->get_accepted_node()->get_expression_name()].push_back(st);
        }

    }

    for (State *st : graph) {
        for (auto it  : st->get_transitions()) {
            inputs.insert(it.first);
        }
    }
    std::vector<std::vector<State * >> rows;
    Table *table = new Table(inputs);
    for (auto it : accepted_states) {
        table->add_row(it.second);
    }
    table->add_row(not_accepted_stats);
    table->init();
    return table;
}
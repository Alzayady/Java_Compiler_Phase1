//
// Created by Hamza on 5/4/2021.
//

#ifndef JAVA_COMPILER_STATE_H
#define JAVA_COMPILER_STATE_H

#include <Node.h>
#include <set>
#include <queue>
#include <map>
#include <unordered_map>
#include <assert.h>
#include <sstream>
#include <Graph.h> // need it to include the epsilon transition

/**
 Custom comparator for the set I use to store the state
 **/

struct cmp {
    bool operator()(Node *a, Node *b) const {
        return a->get_id() < b->get_id();
    }
};

class State {
    std::unordered_map<char, State *> transition;
    bool accepted;
    Node *accepted_node;
    std::set<Node *, cmp> st;

public:

    State();

    std::set<Node* , cmp> *get_state_nodes();

    std::unordered_map<char, State *> get_transitions();

    void add_node(Node *node);

    bool is_accepted();

    Node *get_accepted_node();

    void add_transition(char input, State *next_state);

    std::string to_string();

    std::string get_details();



};

#endif //JAVA_COMPILER_STATE_H


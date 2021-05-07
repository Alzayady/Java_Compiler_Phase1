//
// Created by Hamza on 5/4/2021.
//

#include "State.h"
#include "../NFA/Node.h"
#include "../NFA/Node.cpp"

State::State() {
    accepted = false;
    accepted_node = nullptr;
}
/***
 *
 * @return vector of pointers to the equivalent nodes in the current state sorted in acsending order
 */
std::set<Node* , cmp>* State::get_state_nodes() {
    return &st;
//    std::vector<Node* > ans ;
//    for(auto node_ptr  : st ) {
//        ans.push_back(node_ptr) ;
//    }
//    return &ans ;
}

std::unordered_map<char, State *> State::get_transitions() {
    return transition;
}

void State::add_node(Node *node) {
    st.insert(node);
    if (node->is_accepted()) {
        if (!accepted || (node < accepted_node)) {
            this->accepted = true;
            accepted_node = node;
        }
    }
}

bool State::is_accepted() {
    return accepted;
}

Node *State::get_accepted_node() {
    return accepted_node;
}

void State::add_transition(char input, State *next_state) {
    assert(!transition.count(input));
    transition[input] = next_state;
}

std::string State::to_string() {
    std::stringstream ss;
    ss << "{ ";
    int counter = 0;
    int size = (int) st.size();
    for (auto v : st) {
        ss << v->get_id();
        if ((counter++) + 1 != size) {
            ss << " , ";
        }
    }
    ss << " }";
    return ss.str();
}

std::string State::get_details() {
    std::stringstream ss;
    ss << '[';
    ss << this->to_string();
    for (auto trans : transition) {
        ss << '[';
        ss << trans.first << " : " << trans.second->to_string();
        ss << "] ";
    }
    ss << ']';
    return ss.str();
}

//
//bool State::operator==(const State &other) const {
//    return equal(st.begin(), st.end(), other.st.begin(), other.st.end());
//}
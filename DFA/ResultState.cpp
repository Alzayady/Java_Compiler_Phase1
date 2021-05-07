#include "ResultState.h"
#include <assert.h>
#include <sstream>

ResultState::ResultState(int id) {
    this->id = id;
    this->accepted = false;
}

int ResultState::get_id() {
    return id;
}

std::string ResultState::get_expression_name() {
    return this->expression_name;
}

std::unordered_map<char, ResultState *> ResultState::get_transitions() {
    return transitions;
}

void ResultState::set_expression_name(std::string name) {
    this->expression_name = name;
}

void ResultState::add_transition(char c, ResultState *nxt) {
    assert(!transitions.count(c));
    transitions[c] = nxt;
}

void ResultState::set_as_accepted() {
    this->accepted = true;
}

std::string ResultState::to_string() {
    std::stringstream ss;
    ss << "{ ";
    if (is_accepted()) {
        ss << "*" ;  // star means that the state is accepted
    }
    ss << get_id() << ' ';
    int counter = 0;
    auto mp = get_transitions();
    int sz = mp.size();
    for (auto &p : mp) {
        sz -= 1;
        ss << '[';
        ss << p.first << ',' << p.second->get_id() << ']';
        if (sz) ss << ',';
    }
    if(is_accepted()){
        ss << get_expression_name() ;
    }
    ss << " }";

    return ss.str();

}

bool ResultState::is_accepted() {
    return accepted;
}

//
// Created by Hamza  on 5/4/2021.
//
#include "State.h"
#include "Minimize.h"

std::set<Node *, cmp> get_epsilon_neighbours(Node *root);

std::vector<State *> construct_dfa_without_minimization(Node *root);

void convert_nfa_to_dfa(Node *root) {
    std::vector<State *> dfa = construct_dfa_without_minimization(root);
    Minimize *m = new Minimize(dfa);
    m->run();
}


/**
 *
 * @param root
 * @return all nodes that all reachable from root through an EPSLILON transition (including the root itself)
 */
std::set<Node *, cmp> get_epsilon_neighbours(Node *root) {
    std::set<Node *, cmp> ans;
    ans.insert(root);
    std::queue<Node *> q;
    std::set<int> ids; // store the id of taken nodes in order not to traverse them again
    q.push(root);
    while (!q.empty()) {
        Node *cur = q.front();
        q.pop();
        for (Edge *edge : cur->get_edges()) {
            char value = edge->get_name();
            Node *neighbour = edge->get_node();
            if (value == Graph::LAMBDA && !ids.count(neighbour->get_id())) {
                ans.insert(neighbour);
                q.push(neighbour);
                ids.insert(neighbour->get_id());
            }
        }
    }
    return ans;
}

/***
 *
 * @param root
 * @return vector of states describing the finite state machine without minimization
 */
std::vector<State *> construct_dfa_without_minimization(Node *root) {
    // Get all states that are reachable from the root state through an EPSILON transition (lampda transition)
    State *initial = new State();
    std::set<Node *, cmp> initial_states = get_epsilon_neighbours(root);
    for (auto node : initial_states) {
        initial->add_node(node);
    }
    initial->add_node(root);

    std::vector<State *> state_space; // contains all the  states that we will encounter
    std::queue<State *> q; // to run bfs on the states
    q.push(initial);
    state_space.push_back(initial);
    while (!q.empty()) {
        State *cur = q.front();
        q.pop();
        std::unordered_map<char, std::set<Node *, cmp>> mp;
        for (auto node : *cur->get_state_nodes()) {
            for (auto edge: node->get_edges()) {
                char value = edge->get_name();
                if (value == Graph::LAMBDA) {
                    // we considered epsilon transitions previously so we don't consider them again
                    continue;
                }
                std::set<Node *, cmp> neighbours = get_epsilon_neighbours(edge->get_node());
                for (auto neighbour : neighbours) {
                    mp[value].insert(neighbour);
                }
            }
        }
        for (const auto &map_entry : mp) {
            char value = map_entry.first;
            std::set<Node *, cmp> possible_state = map_entry.second;
            bool repeated = false;
            for (int i = 0; i < (int) state_space.size(); i++) {


                bool same_state = std::equal(state_space[i]->get_state_nodes()->begin(),
                                             state_space[i]->get_state_nodes()->end(), possible_state.begin(),
                                             possible_state.end());
                if (same_state) {
                    repeated = true;
                    (*cur).add_transition(value, state_space[i]);

                }
            }
            if (!repeated) {
                State *new_state = new State();
                for (Node *node : possible_state) {
                    new_state->add_node(node);
                }
                (*cur).add_transition(value, new_state);
                state_space.push_back(new_state);
                q.push(new_state);
            }
        }
    }

    for (int i = 0; i < (int) state_space.size(); i++) {
        std::cout << (state_space[i])->get_details() << std::endl;
    }
    return state_space;
}


// uncommit if you want to test the code
void test_sheet_1() {
    std::cout << "Test 4 started" << std::endl;
    std::vector<Node> a(5);
    auto add_edge = [&](int from, int to, char name) {
        Edge *edge01 = new Edge(&a[to], name);
        a[from].add_edge(edge01);

    };
    add_edge(0, 1, '0');
    add_edge(0, 2, '1');
    add_edge(1, 0, '0');
    add_edge(1, 2, '1');
    add_edge(2, 0, '0');
    add_edge(2, 3, '1');
    add_edge(3, 4, '0');
    add_edge(3, 4, '1');
    add_edge(4, 4, '0');
    add_edge(4, 2, '1');
    std::vector<State *> temp = construct_dfa_without_minimization(&a[0]);
    std::cout << "Test 4 finished" << std::endl;
}

void test1() {
    std::cout << "Test 1 started" << std::endl;
    std::vector<Node> a(7);
    Edge edge01(&a[1], 'a');
    Edge edge02(&a[2], 'a');
    Edge edge03(&a[3], 'b');
    Edge edge14(&a[4], 'b');
    Edge edge25(&a[5], 'b');
    Edge edge36(&a[6], 'a');
    Edge edge12(&a[1], 'a');
    Edge edge11(&a[2], 'a');
    a[0].add_edge(&edge01);
    a[0].add_edge(&edge02);
    a[0].add_edge(&edge03);

    a[1].add_edge(&edge14);
    a[1].add_edge(&edge12);
    a[1].add_edge(&edge11);
    a[2].add_edge(&edge25);
    a[3].add_edge(&edge36);
    convert_nfa_to_dfa(&a[0]);
    /**
     Expected Answer:
     [{ 1 }[a : { 2 , 3 }] [b : { 4 }] ]
    [{ 4 }[a : { 7 }] ]
    [{ 2 , 3 }[b : { 5 , 6 }] [a : { 2 , 3 }] ]
    [{ 7 }]
    [{ 5 , 6 }]
     */
}

void test2() {
    std::cout << "Test 2 started" << std::endl;
    std::vector<Node> a(5);
    auto add_edge = [&](int from, int to, char name) {
        Edge *edge01 = new Edge(&a[to], name);
        a[from].add_edge(edge01);

    };
    add_edge(0, 1, '0');
    add_edge(0, 2, '1');
    add_edge(1, 0, '0');
    add_edge(1, 2, '1');
    add_edge(2, 0, '0');
    add_edge(2, 3, '1');
    add_edge(3, 4, '0');
    add_edge(3, 2, '1');
    add_edge(4, 4, '0');
    add_edge(4, 2, '1');
    a[2].set_expression_name("zozo");
    convert_nfa_to_dfa(&a[0]);
}

void test3() {
    std::cout << "Test 3 started" << std::endl;
    std::vector<Node> a(8);
    auto add_edge = [&](int from, int to, char name) {
        Edge *edge01 = new Edge(&a[to], name);
        a[from].add_edge(edge01);

    };
    add_edge(0, 1, '0');
    add_edge(1, 2, '0');
    add_edge(0, 3, '1');
    add_edge(2, 4, '0');
    add_edge(2, 2, '1');
    add_edge(3, 5, '0');
    add_edge(3, 2, '1');
    add_edge(4, 6, '1');
    add_edge(5, 7, '0');
    add_edge(5, 3, '1');
    add_edge(6, 5, '0');
    add_edge(6, 2, '1');
    add_edge(7, 4, '0');
    add_edge(7, 3, '1');

    a[1].set_expression_name("zozo");
    a[3].set_expression_name("zozo");
    a[4].set_expression_name("zozo");
    a[5].set_expression_name("zozo");
    a[6].set_expression_name("zozo");
    a[7].set_expression_name("zozo");
    convert_nfa_to_dfa(&a[0]);

}

void test_custom() {
    std::cout << "Test 2 started" << std::endl;
    std::vector<Node> a(7);
    Edge edge01(&a[1], Graph::LAMBDA);
    Edge edge02(&a[2], Graph::LAMBDA);
    Edge edge03(&a[3], 'b');
    Edge edge14(&a[4], 'b');
    Edge edge25(&a[5], 'b');
    Edge edge36(&a[6], 'a');
    Edge edge12(&a[1], 'a');
    Edge edge11(&a[2], 'a');
    a[0].add_edge(&edge01);
    a[0].add_edge(&edge02);
    a[0].add_edge(&edge03);

    a[1].add_edge(&edge14);
    a[1].add_edge(&edge12);
    a[1].add_edge(&edge11);
    a[2].add_edge(&edge25);
    a[3].add_edge(&edge36);

    std::vector<State *> states = construct_dfa_without_minimization(&a[0]);
    for (auto s : states) {
        if (s->is_accepted()) {
            std::cout << s->get_accepted_node()->get_id() << std::endl;
        }
    }
    std::cout << "Test 1 finished" << std::endl;

}

int main() {
    test3();
    return 0;
}
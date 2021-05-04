//
// Created by Hamza  on 5/3/2021.
//

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

// vector<state>
class State {
    std::unordered_map<char, State *> transition;
    bool accepted;
    Node *accepted_node;
    std::set<Node *, cmp> st;
public:

    State() {
        accepted = false;
        accepted_node = nullptr;
    }

    std::set<Node *, cmp> *get_state_nodes() {
        return &st;
    }

    void add_node(Node *node) {
        st.insert(node);
        if (node->is_accepted()) {
            if (!accepted || (node < accepted_node)) {
                this->accepted = true;
                accepted_node = node;
            }
        }
    }
    bool is_accepted(){
        return accepted ;
    }
    Node* get_accepted_node(){
        return accepted_node ;
    }
    void add_transition(char input, State *next_state) {
        assert(!transition.count(input));
        transition[input] = next_state;
    }

    std::string to_string() {
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

    std::string get_details() {
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


    bool operator==(const State &other) const {
        return equal(st.begin(), st.end(), other.st.begin(), other.st.end());
    }
};

std::set<Node *> get_epsilon_neighbours(Node *root) {
    std::set<Node *> ans;
    ans.insert(root);
    std::queue<Node *> q;
    std::set<int> ids; // store the id of taken nodes in order not to traverse them again
    while (!q.empty()) {
        Node *cur = q.front();
        q.pop();
        for (Edge *edge : cur->get_edges()) {
            char value = edge->get_name();
            Node *neighbour = edge->get_node();
            if (value == Graph::LAMBDA && !ids.count(neighbour->get_id())) {
                ans.insert(neighbour);
                q.push(edge->get_node());
            }
        }
    }
}

std::vector<State *> construct_dfa_naive(Node *root) {

    std::vector<State *> state_space; // contains all the  states that we will encounter
    std::queue<State *> q; // to run bfs on the states
    State *initial = new State();
    initial->add_node(root);
    q.push(initial);
    state_space.push_back(initial);
    while (!q.empty()) {
        State *cur = q.front();
        q.pop();
        std::unordered_map<char, std::set<Node *, cmp>> mp;
        for (auto node : *cur->get_state_nodes()) {
            for (auto edge: node->get_edges()) {
                char value = edge->get_name();
                Node *neighbour = edge->get_node();
                // add
                mp[value].insert(neighbour);
            }
        }
        for (const auto &map_entry : mp) {
            char value = map_entry.first;
            std::set<Node *, cmp> possible_state = map_entry.second;
            bool repeated = false;
            for (int i = 0; i < (int) state_space.size(); i++) {
                bool same_state = equal(state_space[i]->get_state_nodes()->begin(),
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

void test_graph_1() {

}

int main() {
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
    std::vector<State *> temp = construct_dfa_naive(&a[0]);
    //
    std::cout << "Test 1 started" << std::endl;
    /**
     Expected Answer:
     [{ 1 }[a : { 2 , 3 }] [b : { 4 }] ]
    [{ 4 }[a : { 7 }] ]
    [{ 2 , 3 }[b : { 5 , 6 }] [a : { 2 , 3 }] ]
    [{ 7 }]
    [{ 5 , 6 }]
     */



    // TEST THE CODE
    return 0;
}
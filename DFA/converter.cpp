//
// Created by Hamza  on 5/4/2021.
//
#include "State.h"

#include "LexicalAnalyzer.h"



void test_convert(Node *root, std::string str) {
    std::vector<State *> dfa = construct_dfa_without_minimization(root);
    Minimize *m = new Minimize(dfa, root);
    Table *table = m->run();
    LexicalAnalyzer *hamze = new LexicalAnalyzer(table);
    std::vector<Token *> ans = hamze->convert(str);
    for(Token *  it: ans){
        std::cout<<it->toString()<<std::endl;
    }
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

void test4() {
    // test 4 started
    std::vector<Node> a(8);
    convert_nfa_to_dfa(&a[0]);
    std::cout << "Test Finished " << std::endl;

}
void test5(){
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
    a[4].set_expression_name("second");
    a[5].set_expression_name("zozo");
    a[6].set_expression_name("zozo");
    a[7].set_expression_name("zozo");
    test_convert(&a[0],"0110");
}
//int main() {
//    test5();
//    return 0;
//}

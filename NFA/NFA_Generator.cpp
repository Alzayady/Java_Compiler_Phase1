//
// Created by Manfi on 05/03/21.
//

#include "NFA_Generator.h"

bool debug = false;

void print(std::string name, std::string& expression, Graph* graph) {
    printf("NFA graph for expression %s\n", expression.c_str());
    printf("Start %s graph------------------\n", name.c_str());
    Graph::print(graph->get_start());
    printf("End %s graph-------------------\n\n", name.c_str());
}

void NFA_Generator::add_expression(std::string name, std::string& expression) {
    Graph* graph = to_NFA(expression);
    if (debug) print(name, expression, graph);
    graph->get_end()->set_expression_name(name);
    expressions.push_back(graph);
}

void check_for_and_operation_or_inside_in_the_stack(char token, std::stack<Graph*>& st, std::stack<char>& symbols){
    if (not symbols.empty() and symbols.top() == '&') {
        st.top()->concatenate_with(new Graph(token));
        symbols.pop();
    } else {
        st.push(new Graph(token));
    }
}

void perform_union_or_concatenate_operation(std::stack<Graph*>& st, std::stack<char>& symbols){
    Graph* graph = st.top(); st.pop();
    if (symbols.top() == '&')
        st.top()->concatenate_with(graph);
    else
        st.top()->union_with(graph);
    symbols.pop();
}

void play_with_stacks(char token, std::stack<Graph*>& st, std::stack<char>& symbols){
    if (not symbols.empty() and symbols.top() == '\\') {
        symbols.pop();
        if (token == 'L') {
            token = Graph::LAMBDA;
        }
        check_for_and_operation_or_inside_in_the_stack(token, st, symbols);
    }
    else if (token == '(' or token == '&' or token == '|' or token == '\\') {
        symbols.push(token);
    }
    else if (token == ')') {
        while(symbols.top() not_eq '(') {
            perform_union_or_concatenate_operation(st, symbols);
        }
        symbols.pop();
    }
    else if (token == '*') {
        st.top()->kleene_closure();
    } else {
        check_for_and_operation_or_inside_in_the_stack(token, st, symbols);
    }
}

Graph* NFA_Generator::to_NFA(std::string& expression) {

    std::stack<Graph*> st;
    std::stack<char> symbols;
    for(char token: expression) {
        play_with_stacks(token, st, symbols);
    }
    while(not symbols.empty()) {
        perform_union_or_concatenate_operation(st, symbols);
    }
    return st.top();

}

Node * NFA_Generator::combine() {
    Node* root = new Node;
    for(Graph* expression: expressions) {
        root->add_edge(new Edge(expression->get_start(), Graph::LAMBDA));
        Graph::delete_graph(expression);
    }
    expressions.clear();
    return root;
}

LexicalAnalyzer* NFA_Generator::go() {
    Node* root = combine();
    if (debug) {
        printf("Final NFA graph\n");
        Graph::print(root);
        printf("End of Manfy work b7bkoooooo\n\n");
    }
    GraphAdapter ga ;
    return ga.get_lexical_analyzer(root);
}
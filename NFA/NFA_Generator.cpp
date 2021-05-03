//
// Created by Manfi on 05/03/21.
//

#include "NFA_Generator.h"

#include <utility>

void NFA_Generator::add_expression(std::string name, std::string& expression) {
    Graph* graph = to_NFA(expression);
    graph->get_end()->set_expression_name(name);
    expressions.push_back(graph);
}

Graph* play_with_parentheses(int& index, std::string& expression) {
    Graph* graph;
    for(; index < expression.size() && expression[index] != ')'; ++index) {
        switch (expression[index++]) {
            case '|':
                graph->union_with(play_with_parentheses(index, expression));
                break;
            case '&':
                graph->concatenate_with(play_with_parentheses(index, expression));
                break;
            case '\\':
                if (expression[index] not_eq 'L')
                    graph = new Graph(expression[index]);
                else
                    graph = new Graph(Graph::LAMBDA);
                break;
            case '(':
                graph = play_with_parentheses(index,expression);
                break;
            default:
                graph = new Graph(expression[--index]);
        }
    }
    ++index;
    return graph;
}

Graph* NFA_Generator::to_NFA(std::string& expression) {
    int index = 0;
    return play_with_parentheses(index, expression);
}

Node * NFA_Generator::combine() {
    Node* root = new Node;
    for(Graph* expression: expressions) {
        root->add_edge(new Edge(expression->get_start(), Graph::LAMBDA));
    }
    return root;
}

void NFA_Generator::go() {
    Node* root = combine();
    // call hamza method;
}
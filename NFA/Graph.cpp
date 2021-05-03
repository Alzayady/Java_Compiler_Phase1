//
// Created by Manfi on 05/03/21.
//

#include "Graph.h"

Node* Graph::get_start() {
    return start;
}

Node* Graph::get_end() {
    return end;
}

void Graph::union_with(Graph *graph) {
    Node* new_start = new Node;
    new_start->add_edge(new Edge(get_start(), EPS));
    new_start->add_edge(new Edge(graph->get_start(), EPS));
    start = new_start;

    Node* new_end = new Node;
    get_end()->add_edge(new Edge(new_end, EPS));
    graph->get_end()->add_edge(new Edge(new_end, EPS));

    end = new_end;
}

void Graph::concatenate_with(Graph *graph) {
    end->add_edge(new Edge(graph->get_start(), EPS));
    end = graph->get_end();
}

void Graph::Kleene_closure() {
    get_end()->add_edge(new Edge(get_start(), EPS));

    Node* new_start = new Node;
    Node* new_end = new Node;

    new_start->add_edge(new Edge(new_end, EPS));
    new_start->add_edge(new Edge(get_start(), EPS));
    get_end()->add_edge(new Edge(new_end, EPS));

    start = new_start;
    end = new_end;
}
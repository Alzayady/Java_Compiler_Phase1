//
// Created by Manfi on 05/03/21.
//

#include "Graph.h"

Graph::Graph(char name) {
    start = new Node;
    end = new Node;
    start->add_edge(new Edge(end, name));
}

Node* Graph::get_start() {
    return start;
}

Node* Graph::get_end() {
    return end;
}

void Graph::delete_graph(Graph* graph) {
    delete graph;
}

void Graph::union_with(Graph *graph) {
    Node* new_start = new Node;
    new_start->add_edge(new Edge(get_start(), LAMBDA));
    new_start->add_edge(new Edge(graph->get_start(), LAMBDA));
    start = new_start;

    Node* new_end = new Node;
    get_end()->add_edge(new Edge(new_end, LAMBDA));
    graph->get_end()->add_edge(new Edge(new_end, LAMBDA));

    end = new_end;
    Graph::delete_graph(graph);
}

void Graph::concatenate_with(Graph *graph) {
    end->add_edge(new Edge(graph->get_start(), LAMBDA));
    end = graph->get_end();
    Graph::delete_graph(graph);
}

void Graph::kleene_closure() {
    get_end()->add_edge(new Edge(get_start(), LAMBDA));

    Node* new_start = new Node;
    Node* new_end = new Node;

    new_start->add_edge(new Edge(new_end, LAMBDA));
    new_start->add_edge(new Edge(get_start(), LAMBDA));
    get_end()->add_edge(new Edge(new_end, LAMBDA));

    start = new_start;
    end = new_end;
}

void Graph::print(Node* root) {
    std::queue<Node*> q; q.push(root); std::unordered_set<Edge*> vis;
    while(not q.empty()) {
        Node* f = q.front(); q.pop();
        for(Edge* edge: f->get_edges()) {
            if (vis.find(edge) == vis.end()) {
                std::cout << f->get_id() << " " << edge->get_name() << " " << edge->get_node()->get_id() << std::endl;
                q.push(edge->get_node());
                vis.insert(edge);
            }
        }
    }
}
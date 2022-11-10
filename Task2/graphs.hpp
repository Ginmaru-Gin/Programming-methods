//
// Created by ginmaru on 9/27/22.
//

#pragma once

#include <algorithm>
#include <memory>
#include <random>
#include <stack>
#include <vector>

class Graph {

    std::vector<std::vector<size_t>> data;

public:

    size_t vertices;
    size_t edges;

    class Validator {
    public:
        [[nodiscard]] virtual bool operator()(const Graph &graph, const std::pair<size_t, size_t> &new_edge) = 0;
    };

    Graph() = delete;

    Graph(size_t vertices, size_t edges, Validator &v);

    [[nodiscard]] std::shared_ptr<std::vector<size_t>> euler() const;

    [[nodiscard]] inline size_t size() const { return data.size(); };

    [[nodiscard]] std::vector<size_t> &operator[](size_t index);

    [[nodiscard]] const std::vector<size_t> &operator[](size_t index) const;

    [[nodiscard]] size_t degree(size_t vert) const;

    [[nodiscard]] bool has_edge(const std::pair<size_t, size_t> &edge) const;

    void remove_edge(const std::pair<size_t, size_t> &edge);

    void toCSV(std::ostream &out);
};

std::vector<size_t> &Graph::operator[](size_t index) {
    return data.at(index);
}

const std::vector<size_t> &Graph::operator[](size_t index) const {
    return data.at(index);
}

Graph::Graph(size_t vertices, size_t edges, Graph::Validator &v) : vertices(vertices), edges(0) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> distrib(0, vertices - 1);
    std::pair<size_t, size_t> new_edge;
    data.resize(vertices);
    while (this->edges < edges) {
        do {
            new_edge = {distrib(gen), distrib(gen)};
        } while (not v(*this, new_edge));

        data[new_edge.first].push_back(new_edge.second);
        data[new_edge.second].push_back(new_edge.first);
        ++this->edges;
    }
}

size_t Graph::degree(size_t vert) const {
    return data[vert].size();
}

// TODO RVO to read about
std::shared_ptr<std::vector<size_t>> Graph::euler() const {
    auto path = std::make_shared<std::vector<size_t>>();
    std::stack<size_t> stack;
    // TODO check by criterion
    auto graph = data;
    size_t size = graph.size();
    for (size_t i = 0; i < size; ++i) {
        if (graph[i].size() % 2) {
            stack.push(i);
            break;
        }
    }
    if (stack.empty()) {
        for (size_t i = 0; i < size; ++i) {
            if (not graph[i].empty()) {
                stack.push(i);
                break;
            }
        }
    }
    while (not stack.empty()) {
        size_t u = stack.top();
        if (not graph[u].empty()) {
            size_t v = graph[u].back();
            stack.push(v);
            graph[u].pop_back();
            std::erase(graph[v], u);
        } else {
            path->push_back(u);
            stack.pop();
        }
    }

    return path;
}

bool Graph::has_edge(const std::pair<size_t, size_t> &edge) const {
    return std::ranges::any_of(data[edge.first], [&e = edge](size_t v) -> bool { return v == e.second; });
}

void Graph::remove_edge(const std::pair<size_t, size_t> &edge) {
    std::erase(data[edge.first], edge.second);
    std::erase(data[edge.second], edge.first);
    --edges;
}

void Graph::toCSV(std::ostream &out) {
    for (size_t i = 0; i < vertices; ++i) {
        for (size_t e: data[i]) {
            out << i << ", " << e << std::endl;
        }
    }
}

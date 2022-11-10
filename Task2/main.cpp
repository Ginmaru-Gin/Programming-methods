#include "brackets.hpp"
#include "graphs.hpp"
#include "sort_stack.hpp"
#include "stack_a.hpp"
#include "task_1_1.hpp"
#include "timer.hpp"

#include <iostream>
#include <fstream>
#include <vector>

using
        std::vector,
        std::string,
        std::cout,
        std::endl;

void generateStrings(vector<vector<string>> &vect, size_t count, size_t size, size_t len);

void graphToTxt(Graph &g, std::ofstream &out);

class Validator : public Graph::Validator {

    size_t odd_vertices;

public:

    Validator() : odd_vertices(0) {}

    [[nodiscard]] bool operator()(const Graph &g, const std::pair<size_t, size_t> &new_edge) override {
        if (g.has_edge(new_edge) or new_edge.first == new_edge.second) {
            return false;
        }
        size_t sum_degree = g.degree(new_edge.first) % 2 + g.degree(new_edge.second) % 2;
        size_t new_odd_vertices = odd_vertices;
        switch (sum_degree) {
            case 0:
                new_odd_vertices += 2;
                break;
            case 2:
                new_odd_vertices -= 2;
                break;
            default:
                break;
        }
        if (new_odd_vertices > 2) {
            return false;
        }
        odd_vertices = std::max(static_cast<size_t>(0), new_odd_vertices);
        return true;
    }
};

template<typename T>
class Comparator {
public:
    [[nodiscard]] bool operator()(T first, T second) const {
        return first <= second;
    };
};

int main() {
    Validator weak_euler_criterion;
    Comparator<string> comp;

    // generate data
#ifdef NDEBUG
    const size_t count = 50'000;
#else
    const size_t count = 1'000;
#endif
    const size_t len = 1'000;

    Timer timer;

    std::stack<int> std_stack_int;
    for (size_t i = 0; i < count; ++i) {
        std_stack_int.push(i);
    }
    Comparator<int> int_comp;
    timer.start();
    qsort_stack(std_stack_int, int_comp);
    timer.stop();
    cout << timer.to_string("First test: ") << endl;

    vector<vector<string>> strings;
    timer.start();
    cout << "Data generating ..." << endl;
    generateStrings(strings, 1, count, len);
    timer.stop();
    cout << timer.to_string("Data is generated in ") << endl;

    Stack_a<string> stack_a(count, true);
    std::stack<string> std_stack;

    cout << "std_stack filling ..." << endl;
    fill_stack(std_stack, strings[0], strings[0].size(), false);
    cout << "stack_a filling ..." << endl;
    fill_stack(stack_a, strings[0], strings[0].size(), false);

    cout << "std_stack sorting ..." << endl;
    timer.start();
    sort_stack(std_stack, comp);
    timer.stop();
    cout << timer.to_string("std_stack is sorted in ") << endl;

    cout << "stack_a sorting ..." << endl;
    timer.start();
    sort_stack(stack_a, comp);
    timer.stop();
    cout << timer.to_string("stack_a is sorted in ") << endl;

    while (not std_stack.empty()) std_stack.pop();
    while (stack_a.size() > 0) stack_a.pop();

    cout << "std_stack filling ..." << endl;
    fill_stack(std_stack, strings[0], strings[0].size(), false);
    cout << "stack_a filling ..." << endl;
    fill_stack(stack_a, strings[0], strings[0].size(), false);

    cout << "std_stack qsorting ..." << endl;
    timer.start();
    qsort_stack(std_stack, comp);
    timer.stop();
    cout << timer.to_string("std_stack is qsorted in ") << endl;

    cout << "stack_a qsorting ..." << endl;
    timer.start();
    qsort_stack(stack_a, comp);
    timer.stop();
    cout << timer.to_string("stack_a is qsorted in ") << endl;

    std::string expr = "(([()]({[()([]])]})){})"; // wrong bracket at the 14th position
    bool expr_is_correct = BracketsChecker<char>::check_brackets(expr);
    size_t index_of_intruder = BracketsChecker<char>::find_intruder(expr);

    cout << "Graph generating ..." << endl;
    timer.start();
    Graph g(100, 100, weak_euler_criterion);
    timer.stop();
    cout << timer.to_string("Graph is generated in ") << endl;

    std::ofstream file("graph.txt");
    g.toCSV(file);
    file.close();

    timer.start();
    auto path = g.euler();
    timer.stop();
    cout << timer.to_string("Euler path is found in ") << endl;

    for (size_t i = 1; i < path->size(); ++i) {
        std::pair<size_t, size_t> edge{path->at(i - 1), path->at(i)};
        g.remove_edge(edge);
    }
    return 0;
}

void generateStrings(vector<vector<string>> &vect, size_t count, size_t size, size_t len) {
    vect.clear();
    vect.resize(count);
    ::string str;
    for (auto &v: vect) {
        v.reserve(count);
    }
    for (size_t i = 0; i < size; ++i) {
        str = gen_rand_str(len, len, ALPHABET);
        for (auto &v: vect) {
            v.push_back(str);
        }
    }
}

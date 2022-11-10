#include "stack_a.hpp"
#include "stack_cmp.hpp"
#include "stack_l.hpp"
#include "task_1.hpp"
#include "timer.hpp"

#include <iostream>
#include <stack>
#include <string>

using std::cout,
        std::endl,
        std::string,
        std::stack,
        std::vector;

/* fill in 'vect' with 'count' string-vectors with size 'size'
 * and each string in these vectors has length 'len' */
void generateStrings(vector<vector<string>> &vect, size_t count, size_t size, size_t len);

int main() {
    // generate data
#ifndef NDEBUG
    const size_t count = 1'000;
#else
    const size_t count = 1'000'000;
#endif
    const size_t len = 1'000;

    vector<vector<string>> strings;
    Timer timer_gen_data;
    timer_gen_data.start();
    cout << "Data generating ..." << endl;
    generateStrings(strings, 4, count, len);
    timer_gen_data.stop();
    cout << timer_gen_data.to_string("Data generated in ") << endl;

    Timer timer_stack_a,
            timer_stack_a_move,
            timer_stack_l,
            timer_stack_l_move,
            timer_stack_a_fixed,
            timer_stack_a_fixed_move,
            timer_std_stack,
            timer_std_stack_move;
    Stack_a<string> stack_a(0),
            stack_a_move(0),
            stack_a_fixed(count, true),
            stack_a_fixed_move(count, true);
    Stack_l<string> stack_l,
            stack_l_move;
    stack<string> std_stack,
            std_stack_move;

    // TESTS

    timer_stack_a.start();
    fill_stack(stack_a, strings[0], strings[0].size(), false);
    timer_stack_a.stop();

    timer_stack_l.start();
    fill_stack(stack_l, strings[0], strings[0].size(), false);
    timer_stack_l.stop();

    timer_stack_a_fixed.start();
    fill_stack(stack_a_fixed, strings[0], strings[0].size(), false);
    timer_stack_a_fixed.stop();

    timer_std_stack.start();
    fill_stack(std_stack, strings[0], strings[0].size(), false);
    timer_std_stack.stop();

    timer_stack_a_move.start();
    fill_stack(stack_a_move, strings[0], strings[0].size(), true);
    timer_stack_a_move.stop();

    timer_stack_l_move.start();
    fill_stack(stack_l_move, strings[1], strings[1].size(), true);
    timer_stack_l_move.stop();
    stack_l_move.push("str");

    timer_stack_a_fixed_move.start();
    fill_stack(stack_a_fixed_move, strings[2], strings[2].size(), true);
    timer_stack_a_fixed_move.stop();

    timer_std_stack_move.start();
    fill_stack(std_stack_move, strings[3], strings[3].size(), true);
    timer_std_stack_move.stop();

    // RESULTS
    cout << "RESULTS: " << endl
         << timer_std_stack.to_string("std_stack: ") << endl
         << timer_stack_a.to_string("stack_a: ") << endl
         << timer_stack_a_fixed.to_string("stack_a_fixed: ") << endl
         << timer_stack_l.to_string("stack_l: ") << endl
         << timer_std_stack_move.to_string("std_stack_move: ") << endl
         << timer_stack_a_move.to_string("stack_a_move: ") << endl
         << timer_stack_a_fixed_move.to_string("stack_a_fixed_move: ") << endl
         << timer_stack_l_move.to_string("stack_l_move: ") << endl;

    // TASK_3
    Timer t;
    t.start();
    bool r = stacks_equal(stack_a, std_stack);
    t.stop();
    cout << "equal test: " << t.to_string() << endl;

    // TASK 4
    t.start();
    std_stack.pop();
    std_stack.push("string");
    r = is_substack(stack_a, std_stack);
    t.stop();
    cout << "substack test: " << t.to_string() << endl;

    // TASK 5
    stack<int> s1, s2;
    s1.push(1);
    s1.push(2);
    s1.push(1);
    s1.push(4);
    s1.push(5);
    s1.push(1);
    s1.push(5);

    size_t q = remove_elem(s1, 1);

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

template <typename Stack>
void sort_stack(Stack &s) {

}

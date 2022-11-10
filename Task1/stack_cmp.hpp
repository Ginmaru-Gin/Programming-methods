//
// Created by ginmaru on 9/14/22.
//

#pragma once

#include <stack>
#include <utility>

using std::move;

template<typename Stack1, typename Stack2>
bool stacks_equal(Stack1 &first, Stack2 &second) {
    if (first.size() != second.size()) {
        return false;
    }
    Stack1 first_tmp;
    Stack2 second_tmp;
    bool result = false;
    while (first.size() > 0 and first.top() == second.top()) {
        first_tmp.push(move(first.top()));
        second_tmp.push(move(second.top()));
        first.pop();
        second.pop();
    }
    if (first.size() == 0 and second.size() == 0)
        result = true;
    while (first_tmp.size() > 0) {
        first.push(move(first_tmp.top()));
        second.push(move(second_tmp.top()));
        first_tmp.pop();
        second_tmp.pop();
    }
    return result;
}

template<typename Stack1, typename Stack2>
bool is_substack(Stack1 &stack, Stack2 &substack) {
    Stack1 stack_tmp;
    Stack2 substack_tmp;
    bool result = false;
    while (stack.size() > 0 and stack.size() >= substack.size()) {
        while (substack.size() > 0 and stack.top() == substack.top()) {
            stack_tmp.push(move(stack.top()));
            substack_tmp.push(move(substack.top()));
            stack.pop();
            substack.pop();
        }
        if (substack.size() == 0) {
            result = true;
        }
        while (substack_tmp.size() > 0) {
            stack.push(move(stack_tmp.top()));
            substack.push(move(substack_tmp.top()));
            stack_tmp.pop();
            substack_tmp.pop();
        }
        if (result)
            break;
        stack_tmp.push(move(stack.top()));
        stack.pop();
    }
    while (stack_tmp.size() > 0) {
        stack.push(move(stack_tmp.top()));
        stack_tmp.pop();
    }
    return result;
}

template<typename Stack>
/* returns a count of removed elements */
size_t remove_elem(Stack &stack, T elem) {
    size_t src_size = stack.size();
    Stack stack_tmp;
    while (stack.size() > 0) {
        if (stack.top() != elem) {
            stack_tmp.push(move(stack.top()));
        }
        stack.pop();
    }
    while (stack_tmp.size() > 0) {
        stack.push(move(stack_tmp.top()));
        stack_tmp.pop();
    }
    return src_size - stack.size();
}

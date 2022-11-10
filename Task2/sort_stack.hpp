//
// Created by ginmaru on 9/27/22.
//

#include "stack_a.hpp"

#include <utility>

#pragma once

template<typename Stack>
void move_top(Stack &&src, Stack &dst) {
    dst.push(std::move(src.top()));
    src.pop();
}

template<typename Stack, typename Comparator>
void sort_stack(Stack &s, const Comparator &cmp);

template<typename Stack, typename Comparator>
void qsort_stack(Stack &s, const Comparator &cmp);

template<typename Stack, typename Comparator>
void sort_stack(Stack &s, const Comparator &cmp) {
    Stack sorted, tmp;
    Stack *s_ptr = &s;
    Stack *tmp_ptr = &tmp;

    while (s_ptr->size() > 0) {
        move_top(std::move(*s_ptr), sorted);
        while (s_ptr->size() > 0) {
            bool is_less = cmp(s_ptr->top(), sorted.top());
            if (is_less) {
                move_top(std::move(sorted), *tmp_ptr);
                move_top(std::move(*s_ptr), sorted);
            } else {
                move_top(std::move(*s_ptr), *tmp_ptr);
            }
        }
        std::swap(s_ptr, tmp_ptr);
    }
    while (sorted.size() > 0) {
        move_top(std::move(sorted), s);
    }
}

template<typename Stack, typename Comparator>
void qsort_stack(Stack &s, const Comparator &cmp) {
    if (s.size() <= 1) return;
    Stack left, right;
    auto top = s.top();
    s.pop();
    while (s.size() > 0) {
        if (cmp(s.top(), top)) {
            move_top(std::move(s), left);
        } else {
            move_top(std::move(s), right);
        }
    }

    qsort_stack(left, cmp);
    qsort_stack(right, cmp);

    Stack tmp;
    while (left.size() > 0) {
        move_top(std::move(left), tmp);
    }
    tmp.push(std::move(top));
    while (right.size() > 0) {
        move_top(std::move(right), tmp);
    }

    while (tmp.size() > 0) {
        move_top(std::move(tmp), s);
    }
}

template<typename Comparator>
void qsort_stack(Stack_a<std::string> &s, const Comparator &cmp) {
    if (s.size() <= 1) return;
    size_t size = s.size();
    Stack_a<std::string> left(size, true), right(size, true);
    auto top = s.top();
    s.pop();
    while (s.size() > 0) {
        if (cmp(s.top(), top)) {
            move_top(std::move(s), left);
        } else {
            move_top(std::move(s), right);
        }
    }

    qsort_stack(left, cmp);
    qsort_stack(right, cmp);

    Stack_a<std::string> tmp(size, true);
    while (left.size() > 0) {
        move_top(std::move(left), tmp);
    }
    tmp.push(std::move(top));
    while (right.size() > 0) {
        move_top(std::move(right), tmp);
    }

    while (tmp.size() > 0) {
        move_top(std::move(tmp), s);
    }
}

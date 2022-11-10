//
// Created by ginmaru on 9/10/22.
//
#pragma once

#include "stack_a.hpp"

#include <random>

const std::string ALPHABET = "abcdefghijklmnopqrstuvwxyz";

std::string gen_rand_str(size_t min_len, size_t max_len, const std::string& alph) {
        if (min_len > max_len) {
        // TODO add different messages
        throw std::invalid_argument("Wrong argument");
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> len_distrib(min_len, max_len);
    std::uniform_int_distribution<size_t> char_distrib(0, alph.length() - 1);
    size_t len = len_distrib(gen);
    char buf[len];
    for (size_t i = 0; i < len; ++i) {
        buf[i] = alph[char_distrib(gen)];
    }
    return {buf, len};
}

template <typename T, template<typename> typename Stack>
void fill_stack(Stack<T>& dst, std::vector<T>& src, size_t count, bool move_semantic) {
    if (move_semantic) {
        for (auto &elem: src) {
            dst.push(std::move(elem));
        }
    } else {
        for (auto &elem: src) {
            dst.push(elem);
        }
    }
}
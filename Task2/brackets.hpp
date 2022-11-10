//
// Created by ginmaru on 9/27/22.
//

#pragma once

#include <map>
#include <stack>
#include <string>
#include <set>

using std::size_t;

template<typename Character>
class BracketsChecker {
    static const std::basic_string<Character> brackets;

    static bool is_left(Character bracket) {
        for (size_t i = 0; i < brackets.size(); i += 2) {
            if (brackets[i] == bracket) {
                return true;
            }
        }
        return false;
    }

    static bool is_right(Character bracket) {
        for (size_t i = 1; i < brackets.size(); i += 2) {
            if (brackets[i] == bracket) {
                return true;
            }
        }
        return false;
    }

    static bool is_correct_pair(Character left, Character right) {
        for (size_t i = 0; i < brackets.size(); ++i) {
            if (brackets[i] == left){
                if (brackets[i + 1] == right) {
                    return true;
                }
                else {
                    return false;
                }
            }
        }
        return false;
    }

public:

    static bool check_brackets(const std::basic_string<Character> &expr) {
        std::stack<Character> s;
        for (Character ch: expr) {
            if (is_left(ch)) {
                s.push(ch);
            } else if (not s.empty() and is_correct_pair(s.top(), ch)) {
                s.pop();
            } else {
                return false;
            }
        }
        return s.size() == 0;
    }

    static size_t find_intruder(const std::basic_string<Character> &expr) {
        std::stack<std::pair<Character, size_t>> s;

        size_t len = expr.size();
        s.push({expr.at(0), 0});
        for (size_t i = 1; i < len; ++i) {
            Character ch = expr.at(i);
            if (not s.empty() and is_correct_pair(s.top().first, ch)) {
                s.pop();
            } else {
                s.push({ch, i});
            }
        }
        size_t half_size = s.size() / 2;
        for (int i = 0; i < half_size; ++i) {
            s.pop();
        }

        return s.top().second;
    }
};

template<typename Character>
const std::basic_string<Character> BracketsChecker<Character>::brackets("()[]{}<>");

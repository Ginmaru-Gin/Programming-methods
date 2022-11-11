//
// Created by ginmaru on 10/28/22.
//

#include "parser.hpp"

#include <cmath>
#include <iostream>

using std::cin;

namespace parser {

    // str_term is the term's string with the following this string character
    Term::Term(string str_term) : str(std::move(str_term)) {
        type = term_type::CONST;
        if (std::any_of(str.cbegin(), str.cend(),
                        [](char ch) { return !std::isdigit(int(ch)) and ch != '.'; })) {
            if (str.back() == '(') {
                type = term_type::FUNC;
            } else {
                type = term_type::VAR;
            }
        }
    }

    vector<Term> pars_expr(const string &expr) {
        vector<Term> terms;
        string str = expr;
        string::const_iterator
                end = std::remove_if(str.begin(), str.end(), isspace),
                left = str.cbegin(),
                right = str.cbegin();
        while (left < end) {
            if (is_operator(*left)) {
                right = left + 1;
            } else {
                right = std::find_if(left, end, [](char ch) { return is_operator(ch); });
            }
            terms.emplace_back(Term(string(left, right), term_type::NONE));
            left = right;
        }
        for (auto it = terms.begin(), end = terms.end(); it < end; ++it) {
            auto &term = *it;
            term_type type = term_type::NONE;
            if (is_number(term.str)) {
                type = term_type::CONST;
            } else if (is_bracket(term.str[0])) {
                type = type_of_bracket(term.str[0]);
            } else if (is_operator(term.str[0])) {
                type = term_type::OP;
            } else if (it + 1 != end and (*(it + 1)).str[0] == '(') {
                type = term_type::FUNC;
            } else {
                type = term_type::VAR;
            }
            if (type == term_type::OP and ( it == terms.begin() or (*(it - 1)).type == term_type::OP)) {
                term.str += "u";
                type = term_type::FUNC;
            }
            term.type = type;
        }
        return terms;
    }

    int read_variables() {
        int count = 0;
        string line;
        while (std::getline(cin, line)) {
            auto new_end = std::remove_if(line.begin(), line.end(), isspace);
            line = line.substr(0, new_end - line.begin());
            if (line.empty()) {
                break;
            }
            auto pos = line.find('=');
            string name = line.substr(0, pos);
            float value = std::stof(line.substr(pos + 1));
            variables.emplace(name, value);
            ++count;
        }
        return count;
    }

    float sum(stack<float> &st) {
        float y = st.top();
        st.pop();
        float x = st.top();
        st.pop();
        return x + y;
    }

    float sub(stack<float> &st) {
        float y = st.top();
        st.pop();
        float x = st.top();
        st.pop();
        return x - y;
    }

    float mul(stack<float> &st) {
        float y = st.top();
        st.pop();
        float x = st.top();
        st.pop();
        return x * y;
    }

    float div(stack<float> &st) {
        float y = st.top();
        st.pop();
        float x = st.top();
        st.pop();
        return x / y;
    }

    float abs(stack<float> &st) {
        float x = st.top();
        st.pop();
        return std::fabs(x);
    }

    float pow(stack<float> &st) {
        float y = st.top();
        st.pop();
        float x = st.top();
        st.pop();
        return std::pow(x, y);
    }

    float fact(stack<float> &st) {
        int x = static_cast<int>(st.top());
        st.pop();
        long long result = 1;
        for (int i = 1; i <= x; ++i) {
            result *= i;
        }
        return static_cast<float>(x);
    }

    float neg(stack<float> &st) {
        float x = st.top();
        st.pop();
        return -x;
    }

    float nothing(stack<float> &st) {
        float x = st.top();
        st.pop();
        return x;
    }
}
//
// Created by ginmaru on 10/28/22.
//
#pragma once

#include <functional>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <stack>

namespace parser {

    using
            std::vector,
            std::string,
            std::map,
            std::stack,
            std::function;

    enum term_type {
        NONE,
        CONST,
        VAR,
        FUNC,
        OP,
        L_BR,
        R_BR,
    };

    struct Term {
        string str;
        term_type type;

        Term() = delete;

        explicit Term(string str_term);

        Term(string str, term_type type) : str(std::move(str)), type(type) {}
    };

    float sum(stack<float> &st);

    float sub(stack<float> &st);

    float mul(stack<float> &st);

    float div(stack<float> &st);

    float abs(stack<float> &st);

    float pow(stack<float> &st);

    float fact(stack<float> &st);

    float neg(stack<float> &st);

    float nothing(stack<float> &st);

    const map<char, term_type> brackets{
            {'(', term_type::L_BR},
            {')', term_type::R_BR}
    };
    const map<string, function<float(stack<float> &)>> functions{
            {"sum", function(sum)},
            {"sub", function(sub)},
            {"mul", function(mul)},
            {"div", function(div)},
            {"abs", function(abs)},
            {"pow", function(pow)},
            {"-u",  function(neg)},
            {"+u",  function(nothing)},

            {"+",   function(sum)},
            {"-",   function(sub)},
            {"*",   function(mul)},
            {"/",   function(div)},
            {"^",   function(pow)},
            {"!",   function(fact)},
    };
    const map<char, int> operators{
            {'(', 0},
            {')', 0},
            {'+', 1},
            {'-', 1},
            {'*', 10},
            {'/', 10},
            {'^', 100},
            {'!', 100},
    };

    inline map<string, float> variables;

    inline bool is_operator(char ch) {
        return operators.contains(ch);
    }

    inline int operator_priority(char ch) {
        return operators.at(ch);
    }

    inline bool is_bracket(char ch) {
        return brackets.contains(ch);
    }

    inline term_type type_of_bracket(char ch) {
        return brackets.at(ch);
    }

//    const Operator &get_operator(char ch) {
//        return operators.at(ch);
//    }


    inline bool is_number(const string &str) {
        return not std::any_of(str.cbegin(), str.cend(),
                               [](char ch) { return not std::isdigit(ch) and ch != '.'; });
    }

    vector<Term> pars_expr(const string &expr);
    int read_variables();
}

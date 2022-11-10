//
// Created by ginmaru on 10/28/22.
//

#pragma once

#include <functional>
#include <map>
#include <string>
#include <utility>
#include <vector>

using
        std::vector,
        std::string,
        std::map;

struct Parser {

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
        const string str;
        term_type type;

        Term() = delete;

        explicit Term(string str_term);

        Term(string str, term_type type) : str(std::move(str)), type(type) {}
    };

    struct Variable : Term {
        float value;

        explicit Variable(const string &str, float value)
                : Term(str, term_type::VAR), value(value) {}

        explicit Variable(const string &str, const string &value)
                : Term(str, term_type::VAR), value(std::stof(value)) {}
    };

    struct Operator : Term {
        unsigned char priority;
        unsigned char operands;

        Operator() = delete;

        Operator(char ch, unsigned char operands, unsigned char prior)
                : Term(string{ch}, term_type::OP), priority(prior), operands(operands) {}
    };

    struct Function : Term {
        typedef std::function<float(float)> func_t;
        // TODO functions for variadic arguments
        const func_t func;

        Function() = delete;

        Function(const string &str, func_t function)
                : Term(str, term_type::FUNC), func(std::move(function)) {}
    };

    map<char, term_type> brackets;
    map<string, Function> functions;
    map<char, Operator> operators;
    map<string, Variable> variables;

    Parser() = default;

    Parser(map<char, term_type> brackets, map<string, Function> functions, map<char, Operator> operators,
           map<string, Variable> variables)
            : brackets(std::move(brackets)), operators(std::move(operators)), functions(std::move(functions)),
              variables(std::move(variables)) {}

    [[nodiscard]] vector<Term> pars_expr(const string &expr) const;

    [[nodiscard]] bool is_bracket(char ch) const {
        return brackets.contains(ch);
    }

    [[nodiscard]] term_type type_of_bracket(char ch) const {
        return brackets.at(ch);
    }

    [[nodiscard]] bool is_operator(char ch) const {
        return operators.contains(ch);
    }

    [[nodiscard]] const Operator &get_operator(char ch) const {
        return operators.at(ch);
    }


    [[nodiscard]] static bool is_number(const string &str) {
        return not std::any_of(str.cbegin(), str.cend(),
                           [](char ch) { return not std::isdigit(ch) and ch != '.'; });
    }
};

//
// Created by ginmaru on 10/28/22.
//

#include "parser.hpp"

using Term = Parser::Term;

// str_term is the term's string with the following this string character
Parser::Term::Term(string str_term) : str(std::move(str_term)) {
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

vector<Term> Parser::pars_expr(const string &expr) const {
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
            right = std::find_if(left, end, [this](char ch) { return is_operator(ch); });
        }
        terms.emplace_back(Term(string(left, right), Parser::term_type::NONE));
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
        }
        else {
            type = term_type::VAR;
        }
        term.type = type;
    }
    return terms;
}

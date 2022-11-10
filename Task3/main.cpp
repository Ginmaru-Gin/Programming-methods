#include "parser.hpp"

#include <iostream>
#include <stack>
#include <string>
#include <vector>

using
        std::string,
        std::cout,
        std::cin,
        std::endl,
        std::vector;

int main() {
    Parser parser{
            {{'(', Parser::term_type::L_BR}, {')', Parser::term_type::R_BR}},
            {},
            {{'(', {'(', 0, 10}},
                    {')', {')', 0, 10}},
                    {'+', {'+', 2, 5}},
                    {'-', {'-', 2, 5}}
            },
            {{"var1", Parser::Variable{"var1", 10}}}
    };
    string expr;
    std::getline(cin, expr);
    vector<Parser::Term> terms = parser.pars_expr(expr);
    return 0;
}

vector<Parser::Term> convert_to_postfix_expr(const vector<Parser::Term> &expr) {
    for (const auto &term : expr) {
        switch (term.type) {
            case Parser::term_type::CONST:
            case Parser::term_type::VAR:
                ;
            case Parser::term_type::L_BR:
                ;
            case Parser::term_type::R_BR:
                ;
            case Parser::term_type::FUNC:
                ;
            case Parser::term_type::OP:
                ;
        }
    }
}

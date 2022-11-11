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
        std::vector,
        std::stack;
using namespace parser;

vector<Term> convert_to_postfix_expr(const vector<Term> &expr);
float process_postfix(vector<Term> &expr);

int main() {
    string expr;
    std::getline(cin, expr);
    read_variables();

    vector<Term> terms = pars_expr(expr);
    vector<Term> postfix = convert_to_postfix_expr(terms);
    cout << process_postfix(postfix) << endl;
    return 0;
}

vector<Term> convert_to_postfix_expr(const vector<Term> &expr) {
    vector<Term> output;
    stack<Term> st;
    for (const Term &term: expr) {
        switch (term.type) {
            case term_type::CONST:
            case term_type::VAR:
                output.push_back(term);
                break;
            case term_type::L_BR:
                st.push(term);
                break;
            case term_type::R_BR:
                while (st.top().type != term_type::L_BR) {
                    output.push_back(st.top());
                    st.pop();
                }
                st.pop();
                break;
            case term_type::FUNC:
                while (not st.empty() and st.top().type == term_type::FUNC) {
                    output.push_back(term);
                    st.pop();
                }
                st.push(term);
                break;
            case term_type::OP:
                while (not st.empty()) {
                    if (st.top().type == term_type::L_BR){
                        break;
                    }
                    if (st.top().type == term_type::FUNC or operator_priority(st.top().str[0]) >= operator_priority(term.str[0])) {
                        output.push_back(st.top());
                        st.pop();
                    }
                    else break;
                }
                st.push(term);
                break;
            case term_type::NONE:
                throw std::runtime_error("Wrong expression");
        }
    }
    while (not st.empty()) {
        output.push_back(st.top());
        st.pop();
    }
    return output;
}

float process_postfix(vector<Term> &expr) {
    stack<float> st;
    for (Term &term : expr) {
        switch (term.type) {
            case term_type::CONST:
                st.push(std::stof(term.str));
                break;
            case term_type::VAR:
                st.push(variables.at(term.str));
                break;
            case term_type::OP:
            case term_type::FUNC:
                st.push(functions.at(term.str)(st));
                break;
            default:
                throw std::runtime_error("Wrong expression");
        }
    }
    return st.top();
}

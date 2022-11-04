#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <string>
#include <deque>
#include <stack>

#include "../include/detail.hpp"
#include "../include/token.hpp"

namespace calc
{
    double calculate(const std::string &expr);

    typedef std::deque<token::Token> tokens;

    tokens parse(const std::string &expr);
    tokens to_prefix(const tokens &infix);
    double calculate_impl(const tokens &prefix);

    tokens to_prefix_impl(const tokens &infix);
    
    void put(const char symbol, tokens &infix, std::stack<std::string> &st);
    void calculate_one_operand(const double operand, const detail::Types unary_operator, std::stack<double> &st);
    void calculate_two_operands(const double first_operand, const double second_operand, const detail::Types type_operator, std::stack<double> &st);
}

#endif

#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <string>
#include <deque>

#include "../include/detail.hpp"

namespace calc
{
    double calculate(const std::string &expr);

    class Token
    {
        std::string value;
        detail::Types type;
        detail::PossibleLeftValues possible_left_value;

        detail::Types define_type(const std::string &value);
        detail::PossibleLeftValues define_possible_left_value(const detail::Types type);

    public:
        Token(const std::string &value);
        Token(const char value);
    };

    typedef std::deque<Token> tokens;

    tokens parse(const std::string &expr);
    tokens to_prefix(const tokens &infix);
    double calculate_impl(const tokens &prefix);
}

#endif

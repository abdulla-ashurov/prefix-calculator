#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <string>
#include <deque>

namespace calc
{
    double calculate(const std::string &expr);

    struct Token
    {
        std::string value;
        uint8_t type;
        uint8_t possible_left_value;

        Token(const std::string &value);
    };

    typedef std::deque<Token> tokens;

    tokens parse(const std::string &expr);
    tokens to_prefix(const tokens &infix);
    double calculate_impl(const tokens &prefix);
}

#endif

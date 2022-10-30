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

        const std::string& get_value() const;
        detail::Types get_type() const;
        detail::PossibleLeftValues get_possible_left_value() const;
    };

    typedef std::deque<Token> tokens;

    tokens parse(const std::string &expr);
    tokens to_prefix(const tokens &infix);
    double calculate_impl(const tokens &prefix);

    tokens to_prefix_impl(const tokens &infix);
}

#endif

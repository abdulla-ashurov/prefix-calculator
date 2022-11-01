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

        detail::Types define_type(const std::string &value);

    public:
        Token(const std::string &value, detail::Types type);
        Token(const char value, detail::Types type);
        Token(const std::string &value);
        Token(const char value);

        const std::string& get_value() const;
        detail::Types get_type() const;
    };

    typedef std::deque<Token> tokens;

    tokens parse(const std::string &expr);
    tokens to_prefix(const tokens &infix);
    double calculate_impl(const tokens &prefix);

    tokens to_prefix_impl(const tokens &infix);
}

#endif

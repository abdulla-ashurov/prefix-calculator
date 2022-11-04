#include "../include/token.hpp"

namespace token
{
    Token::Token(const char value)
        : Token(std::string(1, value), define_type(std::string(1, value))) {}

    Token::Token(const std::string &value)
        : Token(value, define_type(value)) {}

    Token::Token(const char value, const detail::Types type)
        : Token(std::string(1, value), type) {}
    
    Token::Token(const std::string &value, const detail::Types type)
        : value(value), type(type) {}

    detail::Types Token::define_type(const std::string &value)
    {
        detail::Types defined_type;

        if (detail::is_operand(value))
            defined_type = detail::Types::OPERAND;
        else if (detail::is_plus(value))
            defined_type = detail::Types::ADDITION;
        else if (detail::is_minus(value))
            defined_type = detail::Types::SUBTRACTION;
        else if (detail::is_multiplication(value))
            defined_type = detail::Types::MULTIPLICATION;
        else if (detail::is_division(value))
            defined_type = detail::Types::DIVISION;
        else if (detail::is_open_bracket(value))
            defined_type = detail::Types::OPEN_BRACKET;
        else if (detail::is_close_bracket(value))
            defined_type = detail::Types::CLOSE_BRACKET;
        else
            defined_type = detail::Types::INCORRECT;

        return defined_type;
    }

    const std::string &Token::get_value() const { return value; }
    detail::Types Token::get_type() const { return type; }
};

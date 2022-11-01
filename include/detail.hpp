#ifndef DETAIL_HPP
#define DETAIL_HPP

#include <string>

namespace detail
{
    enum class Types
    {
        OPERAND = 0b00000001,
        OPEN_BRACKET = 0b00000010,
        CLOSE_BRACKET = 0b00000011,
        ADDITION = 0b00000100,
        SUBTRACTION = 0b00000101,
        MULTIPLICATION = 0b00000110,
        DIVISION = 0b00000111,
        UNARY_MINUS = 0b00001000,
        UNARY_PLUS = 0b00001001,
        INCORRECT = 0b00001010
    };

    bool is_number(const char s);

    bool is_operand(const std::string &value);
    bool is_plus(const std::string &value);
    bool is_minus(const std::string &value);
    bool is_multiplication(const std::string &value);
    bool is_division(const std::string &value);
    bool is_open_bracket(const std::string &value);
    bool is_close_bracket(const std::string &value);
}

#endif

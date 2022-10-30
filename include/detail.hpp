#ifndef DETAIL_HPP
#define DETAIL_HPP

#include <string>

namespace detail
{
    enum class Types
    {
        OPERAND = 0b00000001,
        ADDITION = 0b00000010,
        SUBTRACTION = 0b00000100,
        MULTIPLICATION = 0b00001000,
        DIVISION = 0b00010000,
        OPEN_BRACKET = 0b00100000,
        CLOSE_BRACKET = 0b01000000,
        INCORRECT = 0b10000000
    };

    enum class PossibleLeftValues
    {
        OPERAND = 0b01111110,
        ADDITION = 0b01111111,
        SUBTRACTION = 0b01111111,
        MULTIPLICATION = 0b00000001,
        DIVISION = 0b00000001,
        OPEN_BRACKET = 0b00111110,
        CLOSE_BRACKET = 0b01011110,
        INCORRECT = 0b10000000
    };

    bool is_number(const char s);

    bool is_operand(const std::string &value);
    bool is_addition(const std::string &value);
    bool is_subtraction(const std::string &value);
    bool is_multiplication(const std::string &value);
    bool is_division(const std::string &value);
    bool is_open_bracket(const std::string &value);
    bool is_close_bracket(const std::string &value);
}

#endif

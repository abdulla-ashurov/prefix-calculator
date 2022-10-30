#ifndef DETAIL_HPP
#define DETAIL_HPP

#include <string>

namespace detail
{
    enum class Types
    {
        OPERAND = 0b00000001,
        OPEN_BRACKET = 0b00000010,
        CLOSE_BRACKET = 0b00000100,
        ADDITION = 0b00001000,
        SUBTRACTION = 0b00010000,
        MULTIPLICATION = 0b00100000,
        DIVISION = 0b01000000,
        INCORRECT = 0b10000000
    };

    enum class PossibleLeftValues
    {
        OPERAND = 0b01111010,
        ADDITION = 0b01111111,
        SUBTRACTION = 0b01111111,
        MULTIPLICATION = 0b00000001,
        DIVISION = 0b00000001,
        OPEN_BRACKET = 0b11111010,
        CLOSE_BRACKET = 0b01111100,
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

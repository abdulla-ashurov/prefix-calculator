#ifndef DETAIL_HPP
#define DETAIL_HPP

#include <string>

namespace detail
{
    enum Types
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

    enum PossibleLeftValues
    {
        OPERAND = Types::ADDITION | Types::SUBTRACTION |
                  Types::MULTIPLICATION | Types::DIVISION |
                  Types::OPEN_BRACKET | Types::CLOSE_BRACKET,

        ADDITION = Types::OPERAND | Types::ADDITION |
                   Types::SUBTRACTION | Types::MULTIPLICATION |
                   Types::DIVISION | Types::OPEN_BRACKET |
                   Types::CLOSE_BRACKET,

        SUBTRACTION = Types::OPERAND | Types::ADDITION |
                      Types::SUBTRACTION | Types::MULTIPLICATION |
                      Types::DIVISION | Types::OPEN_BRACKET |
                      Types::CLOSE_BRACKET,

        MULTIPLICATION = Types::OPERAND,

        DIVISION = Types::OPERAND,

        OPEN_BRACKET = Types::ADDITION | Types::SUBTRACTION |
                       Types::MULTIPLICATION | Types::DIVISION |
                       Types::OPEN_BRACKET,

        CLOSE_BRACKET = Types::ADDITION | Types::SUBTRACTION |
                        Types::MULTIPLICATION | Types::DIVISION |
                        Types::CLOSE_BRACKET,

        INCORRECT = Types::INCORRECT
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

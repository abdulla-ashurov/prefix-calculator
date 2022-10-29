#include "../include/detail.hpp"

namespace detail
{
    bool is_number(const char s)
    {
        return s >= '0' && s <= '9';
    }

    uint8_t define_type(std::string &value)
    {
        uint8_t defined_type;

        if (is_operand(value))
            defined_type = Types::OPERAND;
        else if (is_addition(value))
            defined_type = Types::ADDITION;
        else if (is_subtraction(value))
            defined_type = Types::SUBTRACTION;
        else if (is_multiplication(value))
            defined_type = Types::MULTIPLICATION;
        else if (is_division(value))
            defined_type = Types::DIVISION;
        else if (is_open_bracket(value))
            defined_type = Types::OPEN_BRACKET;
        else if (is_close_bracket(value))
            defined_type = Types::CLOSE_BRACKET;
        else
            defined_type = Types::INCORRECT;

        return defined_type;
    }

    uint8_t define_possible_left_value(const Types type)
    {
        uint8_t possible_left_value;

        switch (type)
        {
        case Types::OPERAND:
            possible_left_value = PossibleLeftValues::OPERAND;
            break;

        case Types::ADDITION:
            possible_left_value = PossibleLeftValues::ADDITION;
            break;

        case Types::SUBTRACTION:
            possible_left_value = PossibleLeftValues::SUBTRACTION;
            break;

        case Types::MULTIPLICATION:
            possible_left_value = PossibleLeftValues::MULTIPLICATION;
            break;

        case Types::DIVISION:
            possible_left_value = PossibleLeftValues::DIVISION;
            break;

        case Types::OPEN_BRACKET:
            possible_left_value = PossibleLeftValues::OPEN_BRACKET;
            break;

        case Types::CLOSE_BRACKET:
            possible_left_value = PossibleLeftValues::CLOSE_BRACKET;
            break;

        case Types::INCORRECT:
            possible_left_value = PossibleLeftValues::INCORRECT;
            break;
        }

        return possible_left_value;
    }
}

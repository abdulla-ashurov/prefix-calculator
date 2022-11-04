#include "../include/detail.hpp"

namespace detail
{
    bool is_number(const char s)
    {
        return s >= '0' && s <= '9';
    }

    bool is_operand(const std::string &value)
    {
        for (size_t i = 0; i < value.length(); i++)
            if (!is_number(value[i]))
                return false;
        
        return true;
    }

    bool is_operator(const Types type)
    {
        return  type == detail::Types::ADDITION ||
                type == detail::Types::SUBTRACTION ||
                type == detail::Types::MULTIPLICATION ||
                type == detail::Types::DIVISION ||
                type == detail::Types::UNARY_PLUS ||
                type == detail::Types::UNARY_MINUS;
    }

    bool is_valid_sequence_of_brackets(const calc::tokens &infix)
    {
        size_t open_brackets_count = 0, close_brackets_count = 0;
        
        for (size_t i = 0; i < infix.size(); i++)
        {
            if (infix[i].get_value() == "(")
                open_brackets_count++;
            else if (infix[i].get_value() == ")")
                close_brackets_count++;

            if (open_brackets_count < close_brackets_count)
                return false;
        }

        return true;
    }

    bool is_plus(const std::string &value)
    {
        return value == "+";
    }

    bool is_minus(const std::string &value)
    {
        return value == "-";
    }

    bool is_multiplication(const std::string &value)
    {
        return value == "*";
    }

    bool is_division(const std::string &value)
    {
        return value == "/";
    }

    bool is_open_bracket(const std::string &value)
    {
        return value == "(";
    }

    bool is_close_bracket(const std::string &value)
    {
        return value == ")";
    }
}

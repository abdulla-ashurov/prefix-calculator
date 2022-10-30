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

    bool is_addition(const std::string &value)
    {
        return value == "+";
    }

    bool is_subtraction(const std::string &value)
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

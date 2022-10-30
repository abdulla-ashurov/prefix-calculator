#include "../include/calculator.hpp"
#include "../include/detail.hpp"

namespace calc
{
    double calculate(const std::string &expr)
    {
        tokens infix = parse(expr);
        tokens prefix = to_prefix(infix);

        return calculate_impl(prefix);
    }

    tokens parse(const std::string &expr)
    {
        std::string operand;
        tokens infix;

        for (size_t i = 0; i < expr.length(); i++)
        {
            if (detail::is_number(expr[i]))
                operand.push_back(expr[i]);

            else
            {
                if (!operand.empty())
                {
                    infix.push_back(Token(operand));
                    operand.clear();
                }
                infix.push_back(Token(expr[i]));
            }
        }

        if (!operand.empty())
        {
            infix.push_back(Token(operand));
            operand.clear();
        }

        return infix;
    }

    Token::Token(const std::string &value)
        : value{value}
    {
        type = define_type(value);
        possible_left_value = define_possible_left_value(type);
    }

    Token::Token(const char value)
        : Token(std::string(1, value)) {}
    
    const std::string& Token::get_value() const
    {
        return value;
    }

    detail::Types Token::get_type() const
    {
        return type;
    }

    detail::PossibleLeftValues Token::get_possible_left_value() const
    {
        return possible_left_value;
    }
    

    detail::Types Token::define_type(const std::string &value)
    {
        detail::Types defined_type;

        if (detail::is_operand(value))
            defined_type = detail::Types::OPERAND;
        else if (detail::is_addition(value))
            defined_type = detail::Types::ADDITION;
        else if (detail::is_subtraction(value))
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

    detail::PossibleLeftValues Token::define_possible_left_value(const detail::Types type)
    {
        detail::PossibleLeftValues possible_left_value;

        switch (type)
        {
        case detail::Types::OPERAND:
            possible_left_value = detail::PossibleLeftValues::OPERAND;
            break;

        case detail::Types::ADDITION:
            possible_left_value = detail::PossibleLeftValues::ADDITION;
            break;

        case detail::Types::SUBTRACTION:
            possible_left_value = detail::PossibleLeftValues::SUBTRACTION;
            break;

        case detail::Types::MULTIPLICATION:
            possible_left_value = detail::PossibleLeftValues::MULTIPLICATION;
            break;

        case detail::Types::DIVISION:
            possible_left_value = detail::PossibleLeftValues::DIVISION;
            break;

        case detail::Types::OPEN_BRACKET:
            possible_left_value = detail::PossibleLeftValues::OPEN_BRACKET;
            break;

        case detail::Types::CLOSE_BRACKET:
            possible_left_value = detail::PossibleLeftValues::CLOSE_BRACKET;
            break;

        case detail::Types::INCORRECT:
            possible_left_value = detail::PossibleLeftValues::INCORRECT;
            break;
        }

        return possible_left_value;
    }
}

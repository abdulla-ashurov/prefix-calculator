#include <algorithm>
#include "../include/calculator.hpp"

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
        std::stack<std::string> st;

        for (size_t i = 0; i < expr.length(); i++)
        {
            if (detail::is_number(expr[i]))
                operand.push_back(expr[i]);

            else
            {
                if (!operand.empty())
                {
                    st.push(operand);
                    put_operand(operand, infix);
                }

                put(expr[i], infix, st);
            }
        }

        if (!operand.empty())
            put_operand(operand, infix);

        return infix;
    }

    void put_operand(std::string &operand, tokens &t)
    {
        t.push_back(token::Token(operand));
        operand.clear();
    }

    void put(const char symbol, tokens &t, std::stack<std::string> &st)
    {
        if (detail::is_plus(std::string(1, symbol)))
        {
            if (!st.empty())
                t.push_back(token::Token(symbol, detail::Types::ADDITION));
            else
                t.push_back(token::Token(symbol, detail::Types::UNARY_PLUS));
        }
        else if (detail::is_minus(std::string(1, symbol)))
        {
            if (!st.empty())
                t.push_back(token::Token(symbol, detail::Types::SUBTRACTION));
            else
                t.push_back(token::Token(symbol, detail::Types::UNARY_MINUS));
        }
        else
            t.push_back(token::Token(symbol));

        if (!st.empty())
            st.pop();
    }

    tokens to_prefix(const tokens &infix)
    {
        tokens prefix = to_prefix_impl(infix);

        return prefix;
    }

    tokens to_prefix_impl(const tokens &infix)
    {
        tokens prefix;
        std::stack<token::Token> st;

        size_t open_bracket_count = 0, close_bracket_count = 0;

        for (int i = infix.size() - 1; i >= 0; i--)
        {
            detail::Types type = infix[i].get_type();

            switch (type)
            {
            case detail::Types::OPERAND:
                prefix.push_back(infix[i]);
                break;

            case detail::Types::CLOSE_BRACKET:
                st.push(infix[i]);
                close_bracket_count++;
                break;

            case detail::Types::OPEN_BRACKET:
                while (st.top().get_type() != detail::Types::CLOSE_BRACKET)
                {
                    prefix.push_back(st.top());
                    st.pop();
                }
                st.pop();
                open_bracket_count++;

                break;

            case detail::Types::UNARY_PLUS:
            case detail::Types::UNARY_MINUS:
            case detail::Types::ADDITION:
            case detail::Types::SUBTRACTION:
            case detail::Types::MULTIPLICATION:
            case detail::Types::DIVISION:
                while (!st.empty() && infix[i].get_type() <= st.top().get_type())
                {
                    prefix.push_back(st.top());
                    st.pop();
                }
                st.push(infix[i]);

                break;

            case detail::Types::INCORRECT:
                throw std::invalid_argument("invalid argument");
                break;
            }

            if (open_bracket_count > close_bracket_count)
                throw std::invalid_argument("invalid argument!");
        }

        if (open_bracket_count != close_bracket_count)
            throw std::invalid_argument("invalid argument!");

        while (!st.empty())
        {
            prefix.push_back(st.top());
            st.pop();
        }

        std::reverse(prefix.begin(), prefix.end());

        return prefix;
    }

    double calculate_impl(const tokens &prefix)
    {
        std::stack<double> st;

        for (int i = prefix.size() - 1; i >= 0; i--)
        {
            if (prefix[i].get_type() == detail::Types::OPERAND)
                st.push(std::stoi(prefix[i].get_value()));

            else if (detail::is_operator(prefix[i].get_type()))
            {
                if (st.empty())
                    throw std::invalid_argument("invalid argument!");

                double first_operand = st.top();
                st.pop();

                if (st.empty())
                    calculate_one_operand(first_operand, prefix[i].get_type(), st);
                else
                {
                    double second_operand = st.top();
                    st.pop();

                    calculate_two_operands(first_operand, second_operand, prefix[i].get_type(), st);
                }
            }
            else
                throw std::invalid_argument("invalid argument!");
        }

        if (st.size() != 1)
            throw std::invalid_argument("invalid argument!");

        return st.top();
    }

    void calculate_one_operand(const double operand, const detail::Types unary_operator, std::stack<double> &st)
    {
        switch (unary_operator)
        {
        case detail::Types::UNARY_PLUS:
            st.push(operand);
            break;

        case detail::Types::UNARY_MINUS:
            st.push(-operand);
            break;

        default:
            throw std::invalid_argument("invalid argument!");
            break;
        }
    }

    void calculate_two_operands(const double first_operand, const double second_operand, const detail::Types type_operator, std::stack<double> &st)
    {
        switch (type_operator)
        {
        case detail::Types::UNARY_PLUS:
            st.push(second_operand);
            st.push(first_operand);
            break;

        case detail::Types::UNARY_MINUS:
            st.push(second_operand);
            st.push(-first_operand);
            break;

        case detail::Types::ADDITION:
            st.push(first_operand + second_operand);
            break;

        case detail::Types::SUBTRACTION:
            st.push(first_operand - second_operand);
            break;

        case detail::Types::MULTIPLICATION:
            st.push(first_operand * second_operand);
            break;

        case detail::Types::DIVISION:
            if (second_operand == 0.0)
                throw std::invalid_argument("we cannot division to zero");
            st.push(first_operand / second_operand);
            break;

        default:
            throw std::invalid_argument("invalid argument!");
            break;
        }
    }
}

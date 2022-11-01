#include <algorithm>

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
        std::stack<std::string> st;

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

                    st.push(operand);
                }
                
                put(expr[i], infix, st);
            }
        }

        if (!operand.empty())
        {
            infix.push_back(Token(operand));
            operand.clear();
        }

        return infix;
    }

    void put(const char symbol, tokens &infix, std::stack<std::string> &st)
    {
        if (detail::is_plus(std::string(1, symbol)))
        {
            if (!st.empty())
                infix.push_back(Token(symbol, detail::Types::ADDITION));
            else
                infix.push_back(Token(symbol, detail::Types::UNARY_PLUS));
        }
        else if (detail::is_minus(std::string(1, symbol)))
        {
            if (!st.empty())
                infix.push_back(Token(symbol, detail::Types::SUBTRACTION));
            else
                infix.push_back(Token(symbol, detail::Types::UNARY_MINUS));
        }
        else
            infix.push_back(Token(symbol));

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
        std::stack<Token> st;

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
                break;
            
            case detail::Types::OPEN_BRACKET:
                while (st.top().get_type() != detail::Types::CLOSE_BRACKET)
                {
                    prefix.push_back(st.top());
                    st.pop();
                }
                st.pop();

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
        }

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
            
            else if (prefix[i].get_type() == detail::Types::ADDITION ||
                prefix[i].get_type() == detail::Types::SUBTRACTION ||
                prefix[i].get_type() == detail::Types::MULTIPLICATION ||
                prefix[i].get_type() == detail::Types::DIVISION ||
                prefix[i].get_type() == detail::Types::UNARY_PLUS ||
                prefix[i].get_type() == detail::Types::UNARY_MINUS)
            {
                if (st.empty())
                    throw std::invalid_argument("invalid argument!");
                
                double first_operand = st.top();
                st.pop();

                if (st.empty())
                {
                    if (prefix[i].get_type() == detail::Types::UNARY_PLUS)
                        st.push(first_operand);
                    else if (prefix[i].get_type() == detail::Types::UNARY_MINUS)
                        st.push(-first_operand);
                    else
                        throw std::invalid_argument("invalid argument!");
                }
                else
                {
                    double second_operand = st.top();
                    st.pop();

                    if (prefix[i].get_type() == detail::Types::UNARY_PLUS)
                    {
                        st.push(second_operand);
                        st.push(first_operand);
                    }
                    else if (prefix[i].get_type() == detail::Types::UNARY_MINUS)
                    {
                        st.push(second_operand);
                        st.push(-first_operand);
                    }
                    else if (prefix[i].get_type() == detail::Types::ADDITION)
                        st.push(first_operand + second_operand);
                    else if (prefix[i].get_type() == detail::Types::SUBTRACTION)
                        st.push(first_operand - second_operand);
                    else if (prefix[i].get_type() == detail::Types::MULTIPLICATION)
                        st.push(first_operand * second_operand);
                    else if (prefix[i].get_type() == detail::Types::DIVISION)
                    {
                        if (second_operand == 0.0)
                            throw std::invalid_argument("we cannot division to zero");
                    
                        st.push(first_operand / second_operand);
                    }
                }
                
            }
            else
                throw std::invalid_argument("invalid argument!");
        }

        return st.top();
    }

    Token::Token(const std::string &value, detail::Types type)
        : value{value}, type{type} {}

    Token::Token(const char value, detail::Types type)
        : Token{std::string(1, value), type} {}

    Token::Token(const std::string &value)
        : value{value}
    {
        type = define_type(value);
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
}

#include "catch_amalgamated.hpp"
#include "../include/calculator.hpp"
#include "../include/detail.hpp"

TEST_CASE("test function calc::parse(const std::string &expr)")
{
    SECTION("should return expected_tokens")
    {
        std::deque<std::string> expressions =
        {
            "1", "23", "345", "678", "9012",
            "-/1+*",
            "1+12", "12-123", "-123*1234", "+1234/-12345",
            "(-1)", "(-23)", "(-345)", "(-9)(012)",
            "abcdefghij",
            "1234567890"
        };

        std::deque<calc::tokens> expected_tokens =
        {
            {calc::Token("1")},
            {calc::Token("23")},
            {calc::Token("345")},
            {calc::Token("678")},
            {calc::Token("9012")},
            {calc::Token("-", detail::Types::UNARY_MINUS), calc::Token("/"), calc::Token("1"), calc::Token("+"), calc::Token("*")},
            {calc::Token("1"), calc::Token("+"), calc::Token("12")},
            {calc::Token("12"), calc::Token("-"), calc::Token("123")},
            {calc::Token("-", detail::Types::UNARY_MINUS), calc::Token("123"), calc::Token("*"), calc::Token("1234")},
            {calc::Token("+", detail::Types::UNARY_PLUS), calc::Token("1234"), calc::Token("/"), calc::Token("-", detail::Types::UNARY_MINUS), calc::Token("12345")},
            {calc::Token("("), calc::Token("-", detail::Types::UNARY_MINUS), calc::Token("1"), calc::Token(")")},
            {calc::Token("("), calc::Token("-", detail::Types::UNARY_MINUS), calc::Token("23"), calc::Token(")")},
            {calc::Token("("), calc::Token("-", detail::Types::UNARY_MINUS), calc::Token("345"), calc::Token(")")},
            {calc::Token("("), calc::Token("-", detail::Types::UNARY_MINUS), calc::Token("9"), calc::Token(")"),
                calc::Token("("), calc::Token("012"), calc::Token(")")},
            {calc::Token("a"), calc::Token("b"), calc::Token("c"), calc::Token("d"),
                calc::Token("e"), calc::Token("f"), calc::Token("g"), calc::Token("h"),
                calc::Token("i"), calc::Token("j")},
            {calc::Token("1234567890")}
        };

        for (size_t i = 0; i < expressions.size(); i++) 
        {
            calc::tokens received_tokens = calc::parse(expressions[i]);

            REQUIRE(received_tokens.size() == expected_tokens[i].size());
            for (size_t j = 0; j < received_tokens.size(); j++)
            {   
                REQUIRE(received_tokens[j].get_value() == expected_tokens[i][j].get_value());
                REQUIRE(received_tokens[j].get_type() == expected_tokens[i][j].get_type());
            }
        }
    }
}

TEST_CASE("test function calc::to_prefix(const tokens &infix)")
{
    SECTION("should return expected_prefix")
    {
        std::deque<calc::tokens> infix =
        {
            {calc::Token("1")},
            {calc::Token("23")},
            {calc::Token("345")},
            {calc::Token("9012")},
            {calc::Token("1"), calc::Token("+"), calc::Token("2"), calc::Token("+"), calc::Token("3")},
            {calc::Token("1"), calc::Token("-"), calc::Token("2"), calc::Token("-"), calc::Token("3")},
            {calc::Token("1"), calc::Token("*"), calc::Token("2"), calc::Token("*"), calc::Token("3")},
            {calc::Token("1"), calc::Token("/"), calc::Token("2"), calc::Token("/"), calc::Token("3")},
            {calc::Token("1"), calc::Token("+"), calc::Token("12")},
            {calc::Token("12"), calc::Token("-"), calc::Token("123")},
            {calc::Token("-"), calc::Token("123"), calc::Token("*"), calc::Token("1234")},
            {calc::Token("+"), calc::Token("1234"), calc::Token("/"), calc::Token("-"), calc::Token("12345")},
            {calc::Token("("), calc::Token("-"), calc::Token("1"), calc::Token(")")},
            {calc::Token("("), calc::Token("-"), calc::Token("23"), calc::Token(")")},
            {calc::Token("("), calc::Token("-"), calc::Token("345"), calc::Token(")")},
            {calc::Token("("), calc::Token("-"), calc::Token("9"), calc::Token(")"),
                calc::Token("*"), calc::Token("("), calc::Token("012"), calc::Token(")")},
            {calc::Token("1234567890")}
        };

        std::deque<calc::tokens> expected_prefix =
        {
            {calc::Token("1")},
            {calc::Token("23")},
            {calc::Token("345")},
            {calc::Token("9012")},
            {calc::Token("+"), calc::Token("1"), calc::Token("+"), calc::Token("2"), calc::Token("3")},
            {calc::Token("-"), calc::Token("1"), calc::Token("-"), calc::Token("2"), calc::Token("3")},
            {calc::Token("*"), calc::Token("1"), calc::Token("*"), calc::Token("2"), calc::Token("3")},
            {calc::Token("/"), calc::Token("1"), calc::Token("/"), calc::Token("2"), calc::Token("3")},
            {calc::Token("+"), calc::Token("1"), calc::Token("12")},
            {calc::Token("-"), calc::Token("12"), calc::Token("123")},
            {calc::Token("-"), calc::Token("*"), calc::Token("123"), calc::Token("1234")},
            {calc::Token("+"), calc::Token("-"), calc::Token("/"), calc::Token("1234"), calc::Token("12345")},
            {calc::Token("-"), calc::Token("1")},
            {calc::Token("-"), calc::Token("23")},
            {calc::Token("-"), calc::Token("345")},
            {calc::Token("*"), calc::Token("-"), calc::Token("9"), calc::Token("012")},
            {calc::Token("1234567890")}
        };

        for (size_t i = 0; i < infix.size(); i++) 
        {
            calc::tokens received_prefix = calc::to_prefix(infix[i]);

            REQUIRE(received_prefix.size() == expected_prefix[i].size());
            for (size_t j = 0; j < received_prefix.size(); j++)
            {
                REQUIRE(received_prefix[j].get_value() == expected_prefix[i][j].get_value());
                REQUIRE(received_prefix[j].get_type() == expected_prefix[i][j].get_type());
            }
        }
    }
}

TEST_CASE("test function calc::calculate_impl")
{
    SECTION("function should return expected_results")
    {
        std::deque<calc::tokens> prefix =
        {
            {calc::Token("1")},
            {calc::Token("23")},
            {calc::Token("345")},
            {calc::Token("9012")},
            {calc::Token("+"), calc::Token("1"), calc::Token("+"), calc::Token("2"), calc::Token("3")},
            {calc::Token("-"), calc::Token("1"), calc::Token("-"), calc::Token("2"), calc::Token("3")},
            {calc::Token("*"), calc::Token("1"), calc::Token("*"), calc::Token("2"), calc::Token("3")},
            {calc::Token("/"), calc::Token("1"), calc::Token("/"), calc::Token("2"), calc::Token("3")},
            {calc::Token("+"), calc::Token("1"), calc::Token("12")},
            {calc::Token("-"), calc::Token("12"), calc::Token("123")},
            {calc::Token("-", detail::Types::UNARY_MINUS), calc::Token("*"), calc::Token("123"), calc::Token("1234")},
            {calc::Token("+", detail::Types::UNARY_PLUS), calc::Token("-", detail::Types::UNARY_MINUS), calc::Token("/"), calc::Token("12340"), calc::Token("1234")},
            {calc::Token("-", detail::Types::UNARY_MINUS), calc::Token("1")},
            {calc::Token("-", detail::Types::UNARY_MINUS), calc::Token("23")},
            {calc::Token("-", detail::Types::UNARY_MINUS), calc::Token("345")},
            {calc::Token("1234567890")}
        };

        std::deque<double> expected_results = {1.0, 23.0, 345.0, 9012.0, 6.0, 2.0, 6.0, 1.5, 13.0, -111.0, -151782.0, 
        -10.0, -1.0, -23.0, -345.0, 1234567890};

        for (size_t i = 0; i < prefix.size(); i++) 
        {
            double result = calc::calculate_impl(prefix[i]);
            REQUIRE(result == expected_results[i]);
        }
    }

    SECTION("function should return std::invalid_argument")
    {
        std::deque<calc::tokens> prefix =
        {
            {calc::Token("+")},
            {calc::Token("-")},
            {calc::Token("*")},
            {calc::Token("/")},
            {calc::Token("*9012")},
            {calc::Token("-+/9012/*")},
            {calc::Token("abcdefghij")},
            {calc::Token("a"), calc::Token("b"), calc::Token("c"), calc::Token("d"),
                calc::Token("e"), calc::Token("f"), calc::Token("g"), calc::Token("h"),
                calc::Token("i"), calc::Token("j")},
            {calc::Token("*"), calc::Token("-"), calc::Token("9"), calc::Token("012")}
        };

        for (size_t i = 0; i < prefix.size(); i++)
            REQUIRE_THROWS(calc::calculate_impl(prefix[i]));
    }
}

TEST_CASE("test function calc::calculate")
{
    SECTION("function should return expected_results")
    {
        std::deque<std::string> expressions = {
            "1", "12", "123", "1234",
            "-1", "-12", "--123", "---1234",
            "(-1)", "(-22)", "-(3)", "--(44)",
            "1+2", "22+33", "4+456", "77+8787",
            "-1-2", "-22-334", "-22-33", "31--22",
            "+1+2", "31++22", "-12*65", "-19*-23",
            "-12/3", "-25/-50", "--25/--50", "--25/-50",
            "-(1)", "(-11)", "(-1-22)*6-53", "(-1-22)/23-43",
            "(555-222)/(1+2)*(22-23)", "(555-222)/(1+2)*-(22-23)",
            "2+2*3", "2-2*3", "(2-2)*3", "-(2+2)*3"
        };

        std::deque<double> expected_results = {
            1, 12, 123, 1234,
            -1, -12, 123, -1234,
            -1, -22, -3, 44,
            3, 55, 460, 8864,
            -3, -356, -55, 53,
            3, 53, -780, 437,
            -4, 0.5, 0.5, -0.5,
            -1, -11, -191, -44,
            -111,111,
            8, -4, 0, -12
        };

        for (size_t i = 0; i < expressions.size(); i++)
        {
            double result = calc::calculate(expressions[i]);
            REQUIRE(result == expected_results[i]);
        }
    }

    SECTION("function should return expected_results")
    {
        std::deque<std::string> expressions = {
            "a", "ab", "abc", "abcdefghij",
            "-*1", "-*12", "--/123", "-/--1234"
        };

        for (size_t i = 0; i < expressions.size(); i++)
            REQUIRE_THROWS(calc::calculate(expressions[i]));
    }
}

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
            {calc::Token("-"), calc::Token("/"), calc::Token("1"), calc::Token("+"), calc::Token("*")},
            {calc::Token("1"), calc::Token("+"), calc::Token("12")},
            {calc::Token("12"), calc::Token("-"), calc::Token("123")},
            {calc::Token("-"), calc::Token("123"), calc::Token("*"), calc::Token("1234")},
            {calc::Token("+"), calc::Token("1234"), calc::Token("/"), calc::Token("-"), calc::Token("12345")},
            {calc::Token("("), calc::Token("-"), calc::Token("1"), calc::Token(")")},
            {calc::Token("("), calc::Token("-"), calc::Token("23"), calc::Token(")")},
            {calc::Token("("), calc::Token("-"), calc::Token("345"), calc::Token(")")},
            {calc::Token("("), calc::Token("-"), calc::Token("9"), calc::Token(")"),
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
                REQUIRE(received_tokens[j].get_possible_left_value() == expected_tokens[i][j].get_possible_left_value());
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
                REQUIRE(received_prefix[j].get_possible_left_value() == expected_prefix[i][j].get_possible_left_value());
            }
        }
    }
}
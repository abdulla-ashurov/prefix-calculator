#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include "detail.hpp"

namespace token
{
    class Token
    {
        std::string value;
        detail::Types type;

        detail::Types define_type(const std::string &value);

    public:
        Token(const char value);
        Token(const std::string &value);
        Token(const char value, detail::Types type);
        Token(const std::string &value, const detail::Types type);
        
        const std::string &get_value() const;
        detail::Types get_type() const;
    };
}

#endif

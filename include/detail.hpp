#ifndef DETAIL_HPP
#define DETAIL_HPP

namespace detail
{
    bool is_number(const char s);

    uint8_t define_type(std::string &value);
    uint8_t define_possible_left_value(std::string &value);
}

#endif

#include "../include/calculator.hpp"

namespace calc
{
    double calculate(const std::string &expr)
    {
        tokens infix = parse(expr);
        tokens prefix = to_prefix(infix);
        
        return calculate_impl(prefix);
    }
}

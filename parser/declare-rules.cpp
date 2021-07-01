#include "declare-rules.hpp"

std::string convertCharToString(const std::string &delimiter, char *s)
{
    std::string input(s); // Construct String from Char
    return input.substr(0, input.find(delimiter));
}

void init(char* x)
{
    
}
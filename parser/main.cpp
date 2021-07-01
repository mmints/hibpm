#include "Declare/Declare.hpp" // Context Header
#include "declare-parser.hpp" // Parser Header

namespace yy
{
    void declare::error(location const &loc, const std::string& s) {
        std::cerr << "error at " << loc << ": " << s << std::endl;
    }
}

int main()
{
    hibpm::Declare declare_ctx;
    std::cout << "> ";
    yy::declare parser(declare_ctx); // make a declare parser
    int v = parser.parse(); // and run it

    std::cout << "All Events: " << std::endl;
    for (const auto& e : declare_ctx.getEvents()) {
        std::cout << e.name << std::endl;
    }

    return v; // What is v?
}
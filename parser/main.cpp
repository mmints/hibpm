# include "Declare/Declare.hh" // Context Header
# include "declare.tab.hh" // Parser Header

// WIP

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
    return 0; // What is v?
}
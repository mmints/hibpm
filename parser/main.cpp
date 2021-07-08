#include "Declare/Declare.hpp" // Context Header
#include "declare-parser.hpp" // Parser Header

#include <fstream>

namespace yy
{
    void declare::error(location const &loc, const std::string& s) {
        std::cerr << "error at " << loc << ": " << s << std::endl;
    }
}

extern int yy_scan_string(const char *);


std::string readFileIntoString(const std::string& path) {
    std::ifstream input_file(path);
    if (!input_file.is_open()) {
        std::cerr << "Could not open the file - '"
             << path << "'" << std::endl;
        exit(EXIT_FAILURE);
    }
    return std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}

int main(int argc, char** argv)
{
    hibpm::Declare declare_ctx;
    yy::declare parser(declare_ctx); // make a declare parser
    
    std::string str = readFileIntoString(argv[1]);

    yy_scan_string(str.c_str());
 
    int v = parser.parse(); // and run it

    std::cout << "All Events: " << std::endl;
    for (const auto& e : declare_ctx.getEvents()) {
        std::cout << e.name << std::endl;
    }

    return v; // What is v?
}
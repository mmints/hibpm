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
    std::string str = std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
    str += "\n"; // Add a line to the end of the file.
    return str;
}

int main(int argc, char** argv)
{
    hibpm::Declare declare_ctx;
    yy::declare parser(declare_ctx); // make a declare parser

    if (!argv[1]) {
        std::cout << "Missing Path!" << std::endl;
        std::cout << "Enter a valid path to a declare text file." << std::endl;
        return 1;
    }

    std::string str = readFileIntoString(argv[1]);

    yy_scan_string(str.c_str());
 
    int v = parser.parse(); // and run it

    int count = declare_ctx.getRules().size();
    std::cout << "Count of Rules (Lines): " << std::to_string(count) << std::endl;

    std::cout << "All Events: " << std::endl;
    for (const auto& e : declare_ctx.getEvents()) {
        std::cout << e.name << std::endl;
    }

    std::cout << "Mystery return value of the parser: " << std::to_string(v) << std::endl;

    return v;
}
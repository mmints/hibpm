#include "Solver.h"

// TODO: Move this out of the parser directory

namespace yy
{
    void declare::error(location const &loc, const std::string& s) {
        std::cerr << "error at " << loc << ": " << s << std::endl;
    }
}

extern int yy_scan_string(const char *);

namespace hibpm
{
    void Solver::readFile(const std::string &path)
    {
        std::ifstream input_file(path);
        if (!input_file.is_open()) {
            std::cerr << "Could not open the file - '"
                      << path << "'" << std::endl;
            exit(EXIT_FAILURE);
        }
        std::string str = std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
        str += "\n"; // Add a line to the end of the file.
        m_file = str;
    }

    void Solver::parse()
    {
        yy::declare parser(m_declare_ctx); // make a declare parser
        yy_scan_string(m_file.c_str());
        if (!parser.parse())
            std::cerr << "Parsing Failed!" << std::endl;
        else
            std::cout << "Parsing Succeed!" << std::endl;
    }

    Declare Solver::parseFromFile(std::string path)
    {
        readFile(path);
        parse();
        return m_declare_ctx;
    }
}
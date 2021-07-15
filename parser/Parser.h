#pragma once

#include <string>
#include "Declare/Declare.hpp"

namespace yy
{
    void declare::error(location const &loc, const std::string& s) {
        std::cerr << "error at " << loc << ": " << s << std::endl;
    }
}

extern int yy_scan_string(const char *);

namespace hibpm
{

    class Parser
    {
    public:

        Parser();
        ~Parser() = default;

        Declare parseFromFile(std::string path);

    private:
        std::string m_file; // This string holds the content of a Declare file
        Declare m_declare;

        void readFile(const std::string& path); // read in the file to parse
        void parse(); // Execute parsing of the file

    };
}

#pragma once

// TODO: Move this out of the parser directory

#include <string>
#include <fstream>

#include "Declare/Declare.hpp"  // Context Header
#include "declare-parser.hpp"   // Parser Header

namespace hibpm
{
    class Solver
    {
    public:
        /**
         * Reads in a Declare text files and parse through Bison into a Declare Object.
         * @param path to file.
         * @return Declare Object that represents the Data Structure of the language.
         */
        Declare parseFromFile(std::string path);

    private:
        std::string m_file; // This string holds the content of a Declare file
        Declare m_declare_ctx;

        void readFile(const std::string& path); // read in the file to parse
        void parse(); // Execute parsing of the file
    };
}

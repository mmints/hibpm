#pragma once

#include <string>
#include <fstream>

#include "Declare/Declare.hpp"  // Context Header
#include "declare-parser.hpp"   // Parser Header

#include "Process/Process.hpp"

namespace hibpm
{
    // TODO: Decide if this Class should be the main Solver Class or just a connection to the parser
    // TODO: Turn to Parser
    class Solver
    {
    public:
        /**
         * Reads in a Declare text files and parse through Bison into a Declare Object.
         * @param path to file.
         * @return Declare Object that represents the Data Structure of the language.
         */
        Declare parseFromFile(std::string path);

        Process getProcess();

        Automaton overallProduct(Process& process); // TODO: This function does not belong here!

    private:
        std::string m_file; // This string holds the content of a Declare file
        Declare m_declare_ctx;

        void readFile(const std::string& path); // read in the file to parse
        void parse(); // Execute parsing of the file
    };
}

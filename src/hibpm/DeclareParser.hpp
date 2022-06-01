#pragma once

#include <fstream>
#include <string>

#include "DeclareContext.hpp"                // Context Header
#include "declare-parser/declare-parser.hpp" // Parser Header

namespace hibpm {

class DeclareParser {
public:
  /**
   * Reads in a Declare text files and parse through Bison into a Declare
   * Object.
   * @param path to file.
   * @return Declare Object that represents the Data Structure of the language.
   */
  DeclareContext parseFromFile(std::string path);

private:
  std::string m_file; // This string holds the content of a Declare file
  DeclareContext m_declare_ctx;

  void readFile(const std::string &path); // read in the file to parse
  void parse();                           // Execute parsing of the file
};
} // namespace hibpm

#include <hibpm/Parser.hpp>

using namespace hibpm;

int main(int argc, char** argv)
{
    Parser parser;
    DeclareContext declareContext = parser.parseFromFile("../../../Resources/bpi_2017_kb.txt"); // FIXME: Make a relative path in CMake

    std::cout << declareContext.getEventData().at(0).name << std::endl;

    return 0;
}

#include <hibpm/Parser.hpp>

using namespace hibpm;

int main(int argc, char** argv)
{
    Parser parser;
    parser.parseFromFile("../../../Resources/bpi_2017_kb.txt"); // FIXME: Make a relative path in CMake
    Process process = parser.getProcess();

    std::cout << process.getStates().at(0)->getRule().toSting() << std::endl;

    return 0;
}

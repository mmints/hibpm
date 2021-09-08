#include "Solver.h"

int main(int argc, char** argv)
{
    hibpm::Solver parser;
    hibpm::Declare declareObject;
    if (!argv[1]) {
        std::cout << "Missing Path!" << std::endl;
        std::cout << "Enter a valid path to a declare text file." << std::endl;
        std::cout << "Use default path to test file related from the build directory: ../../DECLARE-examples/bpi_2017_kb.txt" << std::endl;
        declareObject = parser.parseFromFile("../../DECLARE-examples/bpi_2017_kb.txt");
    }
    else {
        declareObject = parser.parseFromFile(argv[1]);
    }

    int count = declareObject.getRules().size();
    std::cout << "Count of Rules (Lines): " << std::to_string(count) << std::endl;

    std::cout << "All Events: " << std::endl;
    for (const auto& e : declareObject.getEvents()) {
        std::cout << e.name << std::endl;
    }

    return 0;
}

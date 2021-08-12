#include "Solver.h"

int main(int argc, char** argv)
{
    if (!argv[1]) {
        std::cout << "Missing Path!" << std::endl;
        std::cout << "Enter a valid path to a declare text file." << std::endl;
        return 1;
    }

    hibpm::Solver parser;
    hibpm::Declare declareObject = parser.parseFromFile(argv[1]);

    int count = declareObject.getRules().size();
    std::cout << "Count of Rules (Lines): " << std::to_string(count) << std::endl;

    std::cout << "All Events: " << std::endl;
    for (const auto& e : declareObject.getEvents()) {
        std::cout << e.name << std::endl;
    }

    return 0;
}
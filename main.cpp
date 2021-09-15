#include "Solver.h"

int main(int argc, char** argv)
{
    hibpm::Solver solver;
    hibpm::Declare declareObject;

    if (!argv[1]) {
        std::cout << "Missing Path!" << std::endl;
        std::cout << "Enter a valid path to a declare text file." << std::endl;
        std::cout << "Use default path to test file related from the build directory: /Resources/bpi_2017_kb.txt" << std::endl;
        declareObject = solver.parseFromFile("../Resources/bpi_2017_kb.txt");
    }
    else {
        declareObject = solver.parseFromFile(argv[1]);
    }

    // Testing Print Outs
    auto count = declareObject.getRules().size();
    std::cout << "Count of Rules (Lines): " << std::to_string(count) << std::endl;

    std::cout << "Rules with numeric event values: " << std::endl;
    for (const auto& rule : declareObject.getRules()) {
        std::cout << rule.type <<": Events: " << rule.events.size() << std::endl;
        for (const auto& event : rule.events) {
            std::cout << event.name << " - " << event.numericValue << std::endl;
        }
    }

    std::cout << "All Events (count:" << declareObject.getEvents().size() << "): " << std::endl;
    for (const auto& e : declareObject.getEvents()) {
        std::cout << e.name << "\t Numeric Value: " << e.numericValue << std::endl;
    }

    return 0;
}

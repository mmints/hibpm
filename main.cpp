#include "Solver.h"

#include "Process/Process.hpp"

int main(int argc, char** argv)
{
    hibpm::Solver solver;
    hibpm::Declare declareKB;

    if (!argv[1]) {
        std::cout << "Missing Path!" << std::endl;
        std::cout << "Enter a valid path to a declare text file." << std::endl;
        std::cout << "Use default path to test file related from the build directory: /Resources/bpi_2017_kb.txt" << std::endl;
        declareKB = solver.parseFromFile("../Resources/bpi_2017_kb.txt");
    }
    else {
        declareKB = solver.parseFromFile(argv[1]);
    }

    // Get process and states
    hibpm::Process process{declareKB};
    std::vector<hibpm::State> states = process.getStates();

    // Testing Print Outs
    auto count = declareKB.getRules().size();
    std::cout << "Count of Rules (Lines): " << std::to_string(count) << std::endl;

    std::cout << "Rules with numeric event values: " << std::endl;
    for (const auto& rule : declareKB.getRules()) {
        std::cout << rule.type <<": Events: " << rule.events.size() << std::endl;
        for (const auto& event : rule.events) {
            std::cout << event.name << " - " << event.numericValue << std::endl;
        }
    }
    std::cout << "______________________________________" << std::endl;

    std::cout << "All Events (count:" << declareKB.getEvents().size() << "): " << std::endl;
    for (const auto& e : declareKB.getEvents()) {
        std::cout << e.name << "\t Numeric Value: " << e.numericValue << std::endl;
    }

    std::cout << "______________________________________" << std::endl;

    std::cout << "Number of states in Process: " << states.size() << std::endl;

    return 0;
}

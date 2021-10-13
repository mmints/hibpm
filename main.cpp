#include "Solver.h"
#include "Repair/RepairAutomata.hpp"

using namespace hibpm;

int main(int argc, char** argv)
{
    Solver solver;
    solver.parseFromFile("../Resources/ruleBaseMod.txt");
    Process process = solver.getProcess();
    RepairAutomata repair;

    Automaton a = process.getStates().at(0)->getAutomata(); // End('O_Sent')
    Automaton b = process.getStates().at(1)->getAutomata(); // NotChainSuccession('O_Sent', 'W_Callincompletefiles')

    RemainderComposition result = repair.controlExpand(process);

    std::cout << "-------------------------------------------------" << std::endl;

    std::cout << "Solution Set Size: " << result.solutionSet.size() << std::endl;
    std::cout << "Hitting Set Size: " << result.hittingSet.size() << std::endl;
    std::cout << "Kernel Set Size: " << result.kernelSet.size() << std::endl;

//    std::cout << "Rules: " << std::endl;
//    for (auto &a: result.solutionSet)
//    {
//        std::cout << a->getRule().type << ": " << std::endl;
//        if (a->isBinary()) {
//            std::cout << "\t Events: " << a->getRule().events[0].name << ", " << a->getRule().events[1].name << std::endl;
//        }
//        else {
//            std::cout << "\t Event: " << a->getRule().events[0].name << std::endl;
//        }
//    }

    return 0;
}

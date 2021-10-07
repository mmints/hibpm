#include "Solver.h"

using namespace hibpm;

int main(int argc, char** argv)
{
    Solver solver;
    solver.parseFromFile("../Resources/declareTest.txt");
    Process process = solver.getProcess();

    Automaton a = process.getStates().at(0)->getAutomata(); // End('O_Sent')
    Automaton b = process.getStates().at(1)->getAutomata(); // NotChainSuccession('O_Sent', 'W_Callincompletefiles')

    std::cout << "Start Product" << std::endl;
    Automaton c = solver.overallProduct();
    std::cout << "Done!" << std::endl;

    c.print();

    return 0;
}

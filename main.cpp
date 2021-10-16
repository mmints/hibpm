#include "Solver.h"
#include "Repair/RepairAutomata.hpp"
#include "Automaton/TopoGraph.h"

using namespace hibpm;

int main(int argc, char** argv)
{
    Solver solver;
    solver.parseFromFile("../Resources/sep.txt");
    Process process = solver.getProcess();
    RepairAutomata repair;

    Automaton a = process.getStates().at(0)->getAutomata(); // End('O_Sent')
    Automaton b = process.getStates().at(1)->getAutomata(); // NotChainSuccession('O_Sent', 'W_Callincompletefiles')


    list<Automaton> automata;

    for (std::shared_ptr<State> s: process.getStates()) {
        automata.push_back(s->getAutomata());
    }

    Automaton auxA;

    std::cout << "size alls  "<<  automata.size() << std::endl;
    std::cout << "rsult of lazy "<<  auxA.lazyProducts(automata) << std::endl;




   // RemainderComposition result = repair.controlExpand(process);
   RemainderComposition result = repair.lazyExpands(process);
        std::cout << "-------------------------------------------------" << std::endl;

    std::cout << "Solution Set Size: " << result.solutionSet.size() << std::endl;
    std::cout << "Hitting Set Size: " << result.hittingSet.size() << std::endl;
    std::cout << "Kernel Set Size: " << result.kernelSet.size() << std::endl;
    set<int> s, in, out, c;
//
//    for (int i = 0; i < 20; ++i) {
//        s.insert(i);
//        c.insert(i+2);
//    }
//
//    a.interComlement(s,c,in,out);
//
//    std::cout << "###" << std::endl;
//    for (int i : out) {
//        std::cout << i << std::endl;
//    }
//
//    std::cout << "###" << std::endl;
//    for (int i : in) {
//        std::cout << i << std::endl;
//    }


//    std::cout << "-------------------------------------------------" << std::endl;
//
//    std::cout << "Solution Set Size: " << result.solutionSet.size() << std::endl;
//    std::cout << "Hitting Set Size: " << result.hittingSet.size() << std::endl;
//    std::cout << "Kernel Set Size: " << result.kernelSet.size() << std::endl;

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

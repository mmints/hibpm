#include <Automaton/Automaton.hpp>
#include "Solver.h"
#include "repair/RepairAutomata.hpp"


// TODO: Move this out of the parser directory

int main(int argc, char** argv)
{
    hibpm::Solver parser;
    hibpm::Declare declareObject;
    if (!argv[1]) {
        std::cout << "Missing Path!" << std::endl;
        std::cout << "Enter a valid path to a declare text file." << std::endl;
        std::cout << "Use default path to test file related from the build directory: /Resources/bpi_2017_kb.txt" << std::endl;
        declareObject = parser.parseFromFile("../Resources/bpi_2017_kb.txt");
    }
    else {
        declareObject = parser.parseFromFile(argv[1]);
    }

    int count = declareObject.getRules().size();
    std::cout << "Count of Rules (Lines): " << std::to_string(count) << std::endl;

    std::cout << "Rules with numeric event values: " << std::endl;
//    for (const auto& rule : declareObject.getRules()) {
//        std::cout << rule.type <<": Events: " << rule.events.size() << std::endl;
//        for (const auto& event : rule.events) {
//            std::cout << event.name << " - " << event.numericValue << std::endl;
//        }
//    }

//    std::cout << "All Events (count:" << declareObject.getEvents().size() << "): " << std::endl;
//    for (const auto& e : declareObject.getEvents()) {
//        std::cout << e.name << "\t Numeric Value: " << e.numericValue << std::endl;
//    }

    hibpm::Automaton a(1,2);
    a.addTransition(0,0,0);
    a.addTransition(0,0,1);
    a.addFinal(0);

    //std::cout << a.transitionsTo[0][0];
    //std::cout << a.transitionsTo[0][1];

    a.print();
    std::cout << "#########" << std::endl;

    //std::cout << a.transitionsTo[0].size();
    hibpm::Automaton b = a.product(&a,&a);
    b.print();
    std::cout << "-----------" << std::endl;
    b.reduceHopcrof()->print();

    RepairAutomata rp;

    list<hibpm::Automaton> ll;
    ll.push_back(b);
    ll.push_back(b);

    int s = rp.expand(ll).size();

    std::cout << s << std::endl;




    return 0;
}

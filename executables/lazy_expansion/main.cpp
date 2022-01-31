#include <hibpm/DeclareParser.hpp>
#include <hibpm/DeclareKnowledgeBase.hpp>
#include <hibpm/RepairAutomata.hpp>

using namespace hibpm;

int main(int argc, char** argv)
{
    DeclareParser parser;
     DeclareContext declareContext = parser.parseFromFile("../../../Resources/chains.txt"); // FIXME: Make a relative path in CMake

    DeclareKnowledgeBase declareKnowledgeBase(declareContext);

    RepairAutomata repairAutomata;

    RemainderComposition remainderComposition;
    remainderComposition = repairAutomata.lazyExpands(declareKnowledgeBase);

    std::cout << "Size of Knowledge Base: " << declareKnowledgeBase.getRuleSet().size() << std::endl;
    std::cout << "Size of Hitting Set: " << remainderComposition.hittingSet.size() << std::endl;

    std::cout << " ---- " << std::endl;

    std::cout << " Hitting Set: " << std::endl;

    for (const auto & hittingSet : remainderComposition.hittingSet)
    {
        hittingSet->print();
    }

    std::cout << " ---- " << std::endl;

    std::cout << " Kernel Set: " << std::endl;

    int i = 0;
    for (const auto & kernelSet : remainderComposition.kernelSet)
    {
        std::cout << " -- " << i << " -- " << std::endl;
        for (const auto & kernel : kernelSet)
        {
            kernel->print();
        }
        i++;
    }

    return 0;
}

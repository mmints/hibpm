#include <hibpm/DeclareParser.hpp>
#include <hibpm/DeclareKnowledgeBase.hpp>
#include <hibpm/RepairAutomata.hpp>

using namespace hibpm;

int main(int argc, char** argv)
{
    DeclareParser parser;
    DeclareContext declareContext = parser.parseFromFile("../../../Resources/BPIC2020/models/sub75_conf12-5_int12-5/RequestForPayment.txt"); // FIXME: Make a relative path in CMake
    DeclareKnowledgeBase declareKnowledgeBase(declareContext);
    RepairAutomata repairAutomata;
    RemainderComposition remainderComposition;
    remainderComposition = repairAutomata.lazyExpands(declareKnowledgeBase);

    for (auto solution : remainderComposition.solutionSet)
    {
        solution->print();
    }

    std::cout << "Size of Knowledge Base: " << declareKnowledgeBase.getConstraintSet().size() << std::endl;
    std::cout << "Size of Solution Set: " << remainderComposition.solutionSet.size() << std::endl;

    return 0;
}

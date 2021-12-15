#include <hibpm/DeclareParser.hpp>
#include <hibpm/RepairAutomata.hpp>

using namespace hibpm;

int main(int argc, char** argv)
{
    DeclareParser parser;
    parser.parseFromFile("../../../Resources/ruleBase.txt"); // FIXME: Make a relative path in CMake
    Process process = parser.getProcess();

    cout << process.getStates().at(0)->getRule().toSting() << endl;

    RepairAutomata repairAutomata;

    RemainderComposition remainderComposition;
    remainderComposition = repairAutomata.lazyExpands(process);

    cout << process.getStates().at(0)->getRule().toSting() << endl;
    cout << remainderComposition.solutionSet.front()->getRule().toSting() << endl;

    for (auto solution : remainderComposition.solutionSet)
    {
        cout << solution->getRule().toSting() << endl;
    }

    return 0;
}

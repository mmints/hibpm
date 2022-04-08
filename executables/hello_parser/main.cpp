#include <hibpm/DeclareParser.hpp>
#include <hibpm/DeclareKnowledgeBase.hpp>

using namespace hibpm;

int main(int argc, char** argv)
{
    // Create a Parser that will handle the input data for this program.
    DeclareParser parser;

    // The Declare Context holds the data given by the DECLARE file.
    // Be aware that this object only holds Data, no further logic.
    // DeclareContext declareContext = parser.parseFromFile("../../../Resources/bpi_2017_kb.txt"); // FIXME: Make a relative path in CMake
    DeclareContext declareContext = parser.parseFromFile("../../../Resources/BPIC2020/models/sup75_conf12-5_int12-5/DomesticDeclarations.txt"); // FIXME: Make a relative path in CMake

    DeclareKnowledgeBase declareKnowledgeBase(declareContext);

    std::vector<shared_ptr<Constraint>> rules = declareKnowledgeBase.getConstraintSet();

    for (auto e : rules) {
        e->print();
    }

    return 0;
}

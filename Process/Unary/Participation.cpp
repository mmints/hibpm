#include "../Unary.hpp" //TODO: Fix CMake to avoid ".."

namespace hibpm
{
    Participation::Participation(Rule &rule, size_t sigmaSize) : Unary(rule, sigmaSize) {
        Participation::initializeAutomaton();
    }

    void Participation::initializeAutomaton() {
        // TODO: Impl
    }
}

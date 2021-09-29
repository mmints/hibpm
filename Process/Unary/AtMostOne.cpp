#include "../Unary.hpp" //TODO: Fix CMake to avoid ".."

namespace hibpm
{
    AtMostOne::AtMostOne(Rule &rule, size_t sigmaSize) : Unary(rule, sigmaSize) {
        AtMostOne::initializeAutomaton();
    }

    void AtMostOne::initializeAutomaton() {
        // TODO: Impl
    }
}

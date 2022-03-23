#include "../Unary.hpp"

namespace hibpm
{
    AtLeastOne::AtLeastOne(size_t sigmaSize, Event &event) :
    Unary(sigmaSize, event)
    {
        m_type = AT_LEAST_ONE;
        m_constraintTypeString = "AtLeastOne";
        m_automaton = Automaton(2, sigmaSize);
        AtLeastOne::initializeAutomaton();
    }

    void AtLeastOne::initializeAutomaton() {
        // TODO
    }
}

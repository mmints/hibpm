#include "../Unary.hpp"

namespace hibpm
{
    AtMostThree::AtMostThree(size_t sigmaSize, Event &event) :
    Unary(sigmaSize, event)
    {
        m_type = AT_MOST_THREE;
        m_constraintTypeString = "AtMostThree";
        m_automaton = Automaton(2, sigmaSize);
        AtMostThree::initializeAutomaton();
    }

    void AtMostThree::initializeAutomaton() {
        // TODO
    }
}

#include "../Unary.hpp"

namespace hibpm
{
    AtMostTwo::AtMostTwo(size_t sigmaSize, Event &event) :
    Unary(sigmaSize, event)
    {
        m_type = AT_MOST_TWO;
        m_constraintTypeString = "AtMostTwo";
        m_automaton = Automaton(2, sigmaSize);
        AtMostTwo::initializeAutomaton();
    }

    void AtMostTwo::initializeAutomaton() {
        // TODO
    }
}

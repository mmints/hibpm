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

        // (0)---|evLetter|--->(2)
        m_automaton.addTransition(0, 2, m_event.numericValue);
        // (1)---|evLetter|--->(2)
        m_automaton.addTransition(1, 2, m_event.numericValue);
        // (2)---|evLetter|--->(3)
        m_automaton.addTransition(2, 3, m_event.numericValue);
        // (3)---|evLetter|--->(4)
        m_automaton.addTransition(3, 4, m_event.numericValue);

        for (int i = 0; i < m_sigmaSize; i++) {
            if (i != m_event.numericValue) {
                // (0)---|Sigma \ evLetter|--->(1)
                m_automaton.addTransition(0, 1, i);
                // (1)---|Sigma \ evLetter|--->(1)
                m_automaton.addTransition(1, 1, i);
                // (2)---|Sigma \ evLetter|--->(2)
                m_automaton.addTransition(2, 2, i);
                // (3)---|Sigma \ evLetter|--->(3)
                m_automaton.addTransition(3, 3, i);
                // (4)---|Sigma \ evLetter|--->(4)
                m_automaton.addTransition(4, 4, i);
            }
        }

        // final
        m_automaton.addFinal(4);
    }
}

#include "../Unary.hpp"

namespace hibpm
{
    Participation::Participation(size_t sigmaSize, Event &event) :
    Unary(sigmaSize, event)
    {
        m_type = PARTICIPATION;
        m_constraintTypeString = "Participation";
        m_automaton = Automaton(2, sigmaSize);
        Participation::initializeAutomaton();
    }

    void Participation::initializeAutomaton() {
        // (0)---|evLetter|--->(1)
        m_automaton.addTransition(0,1,m_event.numericValue);

        for (int a = 0; a < m_sigmaSize; a++)
        {
            // (0)---|Sigma \ evLetter|--->(0)
            if (a != m_event.numericValue) {
                m_automaton.addTransition(0, 0, a);
            }

            // (1)---|Sigma|--->(1)
            m_automaton.addTransition(1, 1, a);

        }

        // final
        m_automaton.addFinal(1);
    }
}

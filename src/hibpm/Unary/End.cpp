#include "../Unary.hpp"

namespace hibpm
{
    End::End(size_t sigmaSize, Event &event) :
    Unary(sigmaSize, event)
    {
        m_type = END;
        m_constraintTypeString = "End";
        m_automaton = Automaton(2, sigmaSize);
        End::initializeAutomaton();
    }

    void End::initializeAutomaton() {
        // (0)---|evLetter|--->(1)
        m_automaton.addTransition(0, 1, m_event.numericValue);

        // (1)---|evLetter|--->(1)
        m_automaton.addTransition(1, 1, m_event.numericValue);


        for (int a = 0; a < m_sigmaSize; a++) {
            if (a != m_event.numericValue)
            {
                // (0)---|Sigma \ evLetter|--->(0)
                m_automaton.addTransition(0, 0, a);

                // (1)---|Sigma \ evLetter|--->(0)
                m_automaton.addTransition(1, 0, a);
            }
        }

        // final
        m_automaton.addFinal(1);
    }
}


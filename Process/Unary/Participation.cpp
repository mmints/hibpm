#include "../Unary.hpp" //TODO: Fix CMake to avoid ".."

namespace hibpm
{
    Participation::Participation(Rule &rule, size_t sigmaSize) : Unary(rule, sigmaSize) {
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

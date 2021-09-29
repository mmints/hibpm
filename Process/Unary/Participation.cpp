#include "../Unary.hpp" //TODO: Fix CMake to avoid ".."

namespace hibpm
{
    Participation::Participation(Rule &rule, size_t sigmaSize) : Unary(rule, sigmaSize) {
        Participation::initializeAutomaton();
    }

    void Participation::initializeAutomaton() {
        // (0)---|evLetter|--->(1)
        m_automaton.addTransition(0,1,m_event.numericValue);

        // (0)---|Sigma \ evLetter|--->(0)
        for (int a = 0; a < m_sigmaSize; a++) {
            if (a != m_event.numericValue) {
                m_automaton.addTransition(0, 0, a);
            }
        }

        // (1)---|Sigma|--->(1)
        for (int a = 0; a < m_sigmaSize; a++) {
            m_automaton.addTransition(1, 1, a);
        }

        // final
        m_automaton.addFinal(1);
    }
}

#include "../Binary.hpp" //TODO: Fix CMake to avoid ".."

namespace hibpm
{
    NotCoExistence::NotCoExistence(Rule &rule, size_t sigmaSize) : Binary(rule, sigmaSize) {
        m_automaton = Automaton(3, sigmaSize);
        NotCoExistence::initializeAutomaton();
    }

    void NotCoExistence::initializeAutomaton() {
        // (0)---| a |--->(1)
        m_automaton.addTransition(0, 1, m_event_1.numericValue);
        // (0)---| b |--->(2)
        m_automaton.addTransition(0, 2, m_event_2.numericValue);

        for (int i = 0; i < m_sigmaSize; i++)
        {
            // (0)---| Sigma \ {a,b} |--->(0)
            if (i != m_event_1.numericValue && i != m_event_2.numericValue) {
                m_automaton.addTransition(0, 0, i);
            }

            // (2)---| Sigma \ a |--->(2)
            if (i != m_event_1.numericValue) {
                m_automaton.addTransition(2, 2, i);
            }

            // (1)---| Sigma \ b |--->(1)
            if (i != m_event_2.numericValue) {
                m_automaton.addTransition(1, 1, i);
            }
        }

        // final
        m_automaton.addFinal(0);
        m_automaton.addFinal(1);
        m_automaton.addFinal(2);
    }
}

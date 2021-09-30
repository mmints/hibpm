#include "../Binary.hpp" //TODO: Fix CMake to avoid ".."

namespace hibpm
{
    NotChainSuccession::NotChainSuccession(Rule &rule, size_t sigmaSize) : Binary(rule, sigmaSize) {
        NotChainSuccession::initializeAutomaton();
    }

    void NotChainSuccession::initializeAutomaton() {
        // (0)---| a |--->(2)
        m_automaton.addTransition(0, 2, m_event_1.numericValue);

        // (1)---| a |--->(2)
        m_automaton.addTransition(1, 2, m_event_1.numericValue);

        // (2)---| a |--->(2)
        m_automaton.addTransition(2, 2, m_event_1.numericValue);

        for (int i = 0; i < m_sigmaSize; i++)
        {
            // (2)---| Sigma \ {a,b} |--->(1)
            if (i != m_event_1.numericValue && i != m_event_2.numericValue) {
                m_automaton.addTransition(2, 1, i);
            }

            // (0)---| Sigma \ a |--->(1)
            // (1)---| Sigma \ a |--->(1)
            if (i != m_event_1.numericValue) {
                m_automaton.addTransition(0, 1, i);
                m_automaton.addTransition(1, 1, i);
            }
        }

        // final
        m_automaton.addFinal(1);
        m_automaton.addFinal(2);
    }
}

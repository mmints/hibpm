#include "../Binary.hpp" //TODO: Fix CMake to avoid ".."

namespace hibpm
{
    ChainSuccession::ChainSuccession(Rule &rule, size_t sigmaSize) : Binary(rule, sigmaSize) {
        ChainSuccession::initializeAutomaton();
    }

    void ChainSuccession::initializeAutomaton() {
        // (0)---| a |--->(2)
        m_automaton.addTransition(0, 2, m_event_1.numericValue);

        // (3)---| a |--->(2)
        m_automaton.addTransition(3, 2, m_event_1.numericValue);

        // (0)---| b |--->(1)
        m_automaton.addTransition(0, 1, m_event_2.numericValue);

        // (2)---| b |--->(3)
        m_automaton.addTransition(2, 3, m_event_2.numericValue);

        for (int i = 0; i < m_sigmaSize; i++) {
            // (0)---| Sigma \ {a,b} |--->(3)
            // (3)---| Sigma \ {a,b} |--->(3)
            if (i != m_event_1.numericValue && i != m_event_2.numericValue) {
                m_automaton.addTransition(0, 3, i);
                m_automaton.addTransition(3, 3, i);
            }
        }

        // final
        m_automaton.addFinal(1);
        m_automaton.addFinal(3);

    }
}

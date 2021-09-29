#include "../Binary.hpp" //TODO: Fix CMake to avoid ".."

namespace hibpm
{
    ChainPrecedence::ChainPrecedence(Rule &rule, size_t sigmaSize) : Binary(rule, sigmaSize) {
        ChainPrecedence::initializeAutomaton();
    }

    void ChainPrecedence::initializeAutomaton() {
        // (0)---| b |--->(1)
        m_automaton.addTransition(0, 1, m_event_2.numericValue);

        // (2)---| a |--->(3)
        m_automaton.addTransition(2, 3, m_event_1.numericValue);

        // (3)---| a |--->(3)
        m_automaton.addTransition(3, 3, m_event_1.numericValue);

        // (0)---| a |--->(3)
        m_automaton.addTransition(0, 3, m_event_1.numericValue);

        for (int i = 0; i < m_sigmaSize; i++)
        {
            if (i != m_event_1.numericValue && i != m_event_2.numericValue)
            {
                // (0)---| Sigma \ {a,b} |--->(2)
                m_automaton.addTransition(0, 2, i);
                // (2)---| Sigma \ {a,b} |--->(2)
                m_automaton.addTransition(2, 2, i);
            }

            // (3)---| Sigma \ a |--->(2)
            if (i != m_event_1.numericValue) {
                m_automaton.addTransition(3, 2, i);
            }
        }
        // final
        m_automaton.addFinal(1);
        m_automaton.addFinal(2);
        m_automaton.addFinal(3);
    }
}

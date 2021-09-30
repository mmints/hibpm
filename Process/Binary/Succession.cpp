#include "../Binary.hpp" //TODO: Fix CMake to avoid ".."

namespace hibpm
{
    Succession::Succession(Rule &rule, size_t sigmaSize) : Binary(rule, sigmaSize) {
        m_automaton = Automaton(3, sigmaSize);
        Succession::initializeAutomaton();
    }

    void Succession::initializeAutomaton() {
        // (0)---| a |--->(1)
        m_automaton.addTransition(0, 1, m_event_1.numericValue);

        // (1)---| b |--->(2)
        m_automaton.addTransition(1, 2, m_event_2.numericValue);

        // (2)---| a |--->(1)
        m_automaton.addTransition(2, 1, m_event_1.numericValue);

        for (int i = 0; i < m_sigmaSize; i++) {
            // (0)---| Sigma \ {a,b} |--->(0)
            if (i != m_event_1.numericValue && i != m_event_2.numericValue) {
                m_automaton.addTransition(0, 0, i);
            }

            // (1)---| Sigma \ b |--->(1)
            if (i != m_event_2.numericValue) {
                m_automaton.addTransition(1, 1, i);
            }

            // (2)---| Sigma \ a |--->(2)
            if (i != m_event_1.numericValue) {
                m_automaton.addTransition(2, 2, i);
            }
        }

        // final
        m_automaton.addFinal(0);
        m_automaton.addFinal(2);
    }
}

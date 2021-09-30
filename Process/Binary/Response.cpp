#include "../Binary.hpp" //TODO: Fix CMake to avoid ".."

namespace hibpm
{
    Response::Response(Rule &rule, size_t sigmaSize) : Binary(rule, sigmaSize) {
        m_automaton = Automaton(2, sigmaSize);
        Response::initializeAutomaton();
    }

    void Response::initializeAutomaton() {
        // (0)---| a |--->(1)
        m_automaton.addTransition(0, 1, m_event_1.numericValue);

        // (1)---| b |--->(0)
        m_automaton.addTransition(1, 0, m_event_2.numericValue);

        for (int i = 0; i < m_sigmaSize; i++)
        {
            // (0)---| Sigma \ a |--->(0)
            if (i != m_event_1.numericValue) {
                m_automaton.addTransition(0, 0, i);
            }

            // (1)---| Sigma \ b |--->(1)
            if ( i != m_event_2.numericValue) {
                m_automaton.addTransition(1, 1, i);
            }
        }

        // final
        m_automaton.addFinal(0);
    }
}

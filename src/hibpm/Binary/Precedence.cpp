#include "../Binary.hpp" //TODO: Fix CMake to avoid ".."

namespace hibpm
{
    Precedence::Precedence(size_t sigmaSize, std::vector<Event> &events) :
    Binary(sigmaSize, events)
    {
        m_type = PRECEDENCE;
        m_ruleTypeString = "Precedence";
        m_automaton = Automaton(2, sigmaSize);
        Precedence::initializeAutomaton();
    }

    void Precedence::initializeAutomaton() {
        // (0)---| a |--->(1)
        m_automaton.addTransition(0, 1, m_event_1.numericValue);

        for (int i = 0; i < m_sigmaSize; i++)
        {
            // (0)---| Sigma \ {a,b} |--->(0)
            if (i != m_event_1.numericValue && i != m_event_2.numericValue) {
                m_automaton.addTransition(0, 0, i);
            }

            // (1)---| Sigma |--->(1)
            m_automaton.addTransition(1, 1, i);
        }

        // final
        m_automaton.addFinal(0);
        m_automaton.addFinal(1);
    }
}

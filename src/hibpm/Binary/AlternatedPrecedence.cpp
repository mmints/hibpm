#include "../Binary.hpp"

namespace hibpm
{
    AlternatedPrecedence::AlternatedPrecedence(size_t sigmaSize, std::vector<Event> &events) :
    Binary(sigmaSize, events)
    {
        m_type = ALTERNATED_PRECEDENCE;
        m_ruleTypeString = "AlternatedPrecedence";
        m_automaton = Automaton(2, sigmaSize);
        AlternatedPrecedence::initializeAutomaton();
    }

    void AlternatedPrecedence::initializeAutomaton() {
        // (0)---| a |--->(1)
        m_automaton.addTransition(0, 1, m_event_1.numericValue);

        // (1)---| b |--->(0)
        m_automaton.addTransition(1, 0, m_event_2.numericValue);


        for (int i = 0; i < m_sigmaSize; i++)
        {
            // (0)---| Sigma \ {a,b} |--->(0)
            if (i != m_event_1.numericValue && i != m_event_2.numericValue) {
                m_automaton.addTransition(0, 0, i);
            }

            // (1)---| Sigma \ b |--->(1)
            if (i != m_event_1.numericValue && i != m_event_2.numericValue) {
                m_automaton.addTransition(1, 1, i);
            }
        }

        // final
        m_automaton.addFinal(0);
        m_automaton.addFinal(1);
    }
}

#include "../Binary.hpp"

namespace hibpm
{
    AlternateSuccession::AlternateSuccession(size_t sigmaSize, std::vector<Event> &events) :
    Binary(sigmaSize, events)
    {
        m_type = ALTERNATED_SUCCESSION;
        m_constraintTypeString = "AlternateSuccession";
        m_automaton = Automaton(2, sigmaSize);
        AlternateSuccession::initializeAutomaton();
    }

    void AlternateSuccession::initializeAutomaton() {
        // (0)---| a |--->(1)
        m_automaton.addTransition(0, 1, m_activation.numericValue);
        // (1)---| b |--->(0)
        m_automaton.addTransition(1, 0, m_target.numericValue);

        // (0)---| Sigma \ {a,b} |--->(0)
        // (1)---| Sigma \ {a,b} |--->(1)
        for (int i = 0; i < m_sigmaSize; i++) {
            if (i != m_activation.numericValue && i != m_target.numericValue) {
                m_automaton.addTransition(0, 0, i);
                m_automaton.addTransition(1, 1, i);
            }
        }

        // final
        m_automaton.addFinal(0);
    }
}

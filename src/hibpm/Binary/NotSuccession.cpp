#include "../Binary.hpp"

namespace hibpm
{
    NotSuccession::NotSuccession(size_t sigmaSize, std::vector<Event> &events) :
    Binary(sigmaSize, events)
    {
        m_type = NOT_SUCCESSION;
        m_constraintTypeString = "NotSuccession";
        m_automaton = Automaton(2, sigmaSize);
        NotSuccession::initializeAutomaton();
    }

    void NotSuccession::initializeAutomaton() {
        // (0)---| a |--->(1)
        m_automaton.addTransition(0, 1, m_activation.numericValue);

        for (int i = 0; i < m_sigmaSize; i++) {
            // (0)---| Sigma \ a |--->(0)
            if (i != m_activation.numericValue) {
                m_automaton.addTransition(0, 0, i);
            }
            // (1)---| Sigma \ b |--->(1)
            if (i != m_target.numericValue) {
                m_automaton.addTransition(1, 1, i);
            }
        }

        // final
        m_automaton.addFinal(0);
        m_automaton.addFinal(1);

    }
}

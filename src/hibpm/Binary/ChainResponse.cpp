#include "../Binary.hpp"

namespace hibpm
{
    ChainResponse::ChainResponse(size_t sigmaSize, std::vector<Event> &events) :
    Binary(sigmaSize, events)
    {
        m_type = CHAIN_RESPONSE;
        m_ruleTypeString = "ChainResponse";
        m_automaton = Automaton(2, sigmaSize);
        ChainResponse::initializeAutomaton();
    }

    void ChainResponse::initializeAutomaton() {
        // (0)---| a |--->(1)
        m_automaton.addTransition(0, 1, m_event_1.numericValue);

        // (1)---| b |--->(0)
        m_automaton.addTransition(1, 0, m_event_2.numericValue);

        // (0)---| Sigma \ a |--->(0)
        for (int i = 0; i < m_sigmaSize; i++) {
            if (i != m_event_1.numericValue) {
                m_automaton.addTransition(0, 0, i);
            }
        }

        // final
        m_automaton.addFinal(0);
    }
}
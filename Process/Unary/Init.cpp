#include "../Unary.hpp" //TODO: Fix CMake to avoid ".."

namespace hibpm
{
    Init::Init(Rule &rule, size_t sigmaSize) : Unary(rule, sigmaSize) {
        m_automaton = Automaton(2, sigmaSize);
        Init::initializeAutomaton();
    }

    void Init::initializeAutomaton() {
        // (0)---|evLetter|--->(1)
        m_automaton.addTransition(0,1,m_event.numericValue);

        // (1)---|Sigma|--->(1)
        for (int a = 0; a < m_sigmaSize; a++) {
            m_automaton.addTransition(1, 1, a);
        }

        // final
        m_automaton.addFinal(1);
    }
}

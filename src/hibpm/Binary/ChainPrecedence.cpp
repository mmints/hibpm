/**
 * @author: Mark O. Mints
 * @email: mmints@uni-koblenz.de
 */

#include "../Binary.hpp"

namespace hibpm {
ChainPrecedence::ChainPrecedence(size_t sigmaSize, std::vector<Event> &events)
    : Binary(sigmaSize, events) {
  m_type = CHAIN_PRECEDENCE;
  m_constraintTypeString = "ChainPrecedence";
  m_automaton = Automaton(4, sigmaSize);
  ChainPrecedence::initializeAutomaton();
}

void ChainPrecedence::initializeAutomaton() {
  // (0)---| b |--->(1)
  m_automaton.addTransition(0, 1, m_target.numericValue);

  // (2)---| a |--->(3)
  m_automaton.addTransition(2, 3, m_activation.numericValue);

  // (3)---| a |--->(3)
  m_automaton.addTransition(3, 3, m_activation.numericValue);

  // (0)---| a |--->(3)
  m_automaton.addTransition(0, 3, m_activation.numericValue);

  for (int i = 0; i < m_sigmaSize; i++) {
    if (i != m_activation.numericValue && i != m_target.numericValue) {
      // (0)---| Sigma \ {a,b} |--->(2)
      m_automaton.addTransition(0, 2, i);
      // (2)---| Sigma \ {a,b} |--->(2)
      m_automaton.addTransition(2, 2, i);
    }

    // (3)---| Sigma \ a |--->(2)
    if (i != m_activation.numericValue) {
      m_automaton.addTransition(3, 2, i);
    }
  }
  // final
  m_automaton.addFinal(1);
  m_automaton.addFinal(2);
  m_automaton.addFinal(3);
}
} // namespace hibpm

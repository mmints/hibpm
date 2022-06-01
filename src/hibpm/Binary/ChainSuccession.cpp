/**
 * @author: Mark O. Mints
 * @email: mmints@uni-koblenz.de
 */

#include "../Binary.hpp"

namespace hibpm {
ChainSuccession::ChainSuccession(size_t sigmaSize, std::vector<Event> &events)
    : Binary(sigmaSize, events) {
  m_type = CHAIN_SUCCESSION;
  m_constraintTypeString = "ChainSuccession";
  m_automaton = Automaton(4, sigmaSize);
  ChainSuccession::initializeAutomaton();
}

void ChainSuccession::initializeAutomaton() {
  // (0)---| a |--->(2)
  m_automaton.addTransition(0, 2, m_activation.numericValue);

  // (3)---| a |--->(2)
  m_automaton.addTransition(3, 2, m_activation.numericValue);

  // (0)---| b |--->(1)
  m_automaton.addTransition(0, 1, m_target.numericValue);

  // (2)---| b |--->(3)
  m_automaton.addTransition(2, 3, m_target.numericValue);

  for (int i = 0; i < m_sigmaSize; i++) {
    // (0)---| Sigma \ {a,b} |--->(3)
    // (3)---| Sigma \ {a,b} |--->(3)
    if (i != m_activation.numericValue && i != m_target.numericValue) {
      m_automaton.addTransition(0, 3, i);
      m_automaton.addTransition(3, 3, i);
    }
  }

  // final
  m_automaton.addFinal(1);
  m_automaton.addFinal(3);
}
} // namespace hibpm

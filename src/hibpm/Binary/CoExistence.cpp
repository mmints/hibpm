/**
 * @author: Mark O. Mints
 * @email: mmints@uni-koblenz.de
 */

#include "../Binary.hpp"

namespace hibpm {
CoExistence::CoExistence(size_t sigmaSize, std::vector<Event> &events)
    : Binary(sigmaSize, events) {
  m_type = CO_EXISTENCE;
  m_constraintTypeString = "CoExistence";
  m_automaton = Automaton(4, sigmaSize);
  CoExistence::initializeAutomaton();
}

void CoExistence::initializeAutomaton() {
  // (0)---| a |--->(1)
  m_automaton.addTransition(0, 1, m_activation.numericValue);

  // (2)---| a |--->(3)
  m_automaton.addTransition(2, 3, m_activation.numericValue);

  // (1)---| b |--->(3)
  m_automaton.addTransition(1, 3, m_target.numericValue);

  // (0)---| b |--->(2)
  m_automaton.addTransition(0, 2, m_target.numericValue);

  for (int i = 0; i < m_sigmaSize; i++) {
    // (0)---| Sigma \ {a,b} |--->(0)
    if (i != m_activation.numericValue && i != m_target.numericValue) {
      m_automaton.addTransition(0, 0, i);
    }

    // (1)---| Sigma \ b |--->(1)
    if (i != m_target.numericValue) {
      m_automaton.addTransition(1, 1, i);
    }

    // (2)---| Sigma \ a |--->(2)
    if (i != m_activation.numericValue) {
      m_automaton.addTransition(2, 2, i);
    }

    // (3)---| Sigma |--->(3)
    m_automaton.addTransition(3, 3, i);
  }

  // final
  m_automaton.addFinal(0);
  m_automaton.addFinal(3);
}
} // namespace hibpm

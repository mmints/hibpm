/**
 * @author: Mark O. Mints
 * @email: mmints@uni-koblenz.de
 */

#include "../Binary.hpp"

namespace hibpm {
Response::Response(size_t sigmaSize, std::vector<Event> &events)
    : Binary(sigmaSize, events) {
  m_type = RESPONSE;
  m_constraintTypeString = "Response";
  m_automaton = Automaton(2, sigmaSize);
  Response::initializeAutomaton();
}

void Response::initializeAutomaton() {
  // (0)---| a |--->(1)
  m_automaton.addTransition(0, 1, m_activation.numericValue);

  // (1)---| b |--->(0)
  m_automaton.addTransition(1, 0, m_target.numericValue);

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
}
} // namespace hibpm

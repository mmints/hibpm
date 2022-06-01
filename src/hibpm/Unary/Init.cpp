/**
 * @author: Mark O. Mints
 * @email: mmints@uni-koblenz.de
 */

#include "../Unary.hpp"

namespace hibpm {
Init::Init(size_t sigmaSize, Event &event) : Unary(sigmaSize, event) {
  m_type = INIT;
  m_constraintTypeString = "Init";
  m_automaton = Automaton(2, sigmaSize);
  Init::initializeAutomaton();
}

void Init::initializeAutomaton() {
  // (0)---|evLetter|--->(1)
  m_automaton.addTransition(0, 1, m_event.numericValue);

  // (1)---|Sigma|--->(1)
  for (int a = 0; a < m_sigmaSize; a++) {
    m_automaton.addTransition(1, 1, a);
  }

  // final
  m_automaton.addFinal(1);
}
} // namespace hibpm

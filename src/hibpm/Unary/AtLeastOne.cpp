/**
 * @author: Mark O. Mints
 * @email: mmints@uni-koblenz.de
 */

#include "../Unary.hpp"

namespace hibpm {
AtLeastOne::AtLeastOne(size_t sigmaSize, Event &event)
    : Unary(sigmaSize, event) {
  m_type = AT_LEAST_ONE;
  m_constraintTypeString = "AtLeastOne";
  m_automaton = Automaton(2, sigmaSize);
  AtLeastOne::initializeAutomaton();
}

void AtLeastOne::initializeAutomaton() {
  // (0)---|evLetter|--->(1)
  m_automaton.addTransition(0, 1, m_event.numericValue);

  for (int a = 0; a < m_sigmaSize; a++) {
    // (0)---|Sigma|--->(0)
    m_automaton.addTransition(0, 0, a);

    // (1)---|Sigma|--->(1)
    m_automaton.addTransition(1, 1, a);
  }

  // final
  m_automaton.addFinal(1);
}
} // namespace hibpm

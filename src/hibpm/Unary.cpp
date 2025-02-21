/**
 * @author: Mark O. Mints
 * @email: mmints@uni-koblenz.de
 */

#include "Unary.hpp"

namespace hibpm {
Unary::Unary(size_t sigmaSize, Event &event)
    : Constraint(sigmaSize, false), m_event(event) {}

Event Unary::getEvent() { return m_event; }

u_int64_t Unary::getEventNumericValue() { return m_event.numericValue; }

bool Unary::eventsMatch(Constraint &rule) {
  if (rule.isUnary()) {
    auto unary = (Unary *)&rule;
    if (m_event.numericValue == unary->getEventNumericValue()) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

Event Unary::getTarget() { return m_event; }

std::string Unary::print() {
  std::string out = m_constraintTypeString + "('" + m_event.name + "')";
  return out;
}
} // namespace hibpm
/**
 * @author: Mark O. Mints
 * @email: mmints@uni-koblenz.de
 */

#include "Binary.hpp"

namespace hibpm {
Binary::Binary(size_t sigmaSize, std::vector<Event> &events)
    : Constraint(sigmaSize, true), m_activation(events.at(0)),
      m_target(events.at(1)) {}

std::vector<Event> Binary::getEvents() { return {m_activation, m_target}; }

std::vector<u_int64_t> Binary::getEventNumericValues() {
  return {m_activation.numericValue, m_target.numericValue};
}

bool Binary::eventsMatch(Constraint &rule) {
  if (rule.isBinary()) {
    auto binary = (Binary *)&rule;
    if (m_activation.numericValue == binary->getEventNumericValues().at(0) &&
        m_target.numericValue == binary->getEventNumericValues().at(1)) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

Event Binary::getTarget() { return m_target; }

std::string Binary::print() {
  std::string out = m_constraintTypeString + "('" + m_activation.name + "','" +
                    m_target.name + "')";
  return out;
}
} // namespace hibpm

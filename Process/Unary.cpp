#include "Unary.hpp"

namespace hibpm
{
    Unary::Unary(Rule &rule, size_t sigmaSize) :
    State(rule, sigmaSize, false),
    m_event(rule.events[0])
    {}

    Event Unary::getEvent() {
        return m_event;
    }

    u_int64_t Unary::getEventNumericValue() {
        return m_event.numericValue;
    }
}
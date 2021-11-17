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

    bool Unary::isEqualTo(Unary &rule) {
        if (m_event.numericValue == rule.m_event.numericValue) {
            return true;
        }
        else {
            return false;
        }
    }

    Event Unary::getTarget() {
        return m_event;
    }
}
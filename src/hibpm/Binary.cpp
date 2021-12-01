#include "Binary.hpp"

namespace hibpm
{
    Binary::Binary(Rule &rule, size_t sigmaSize) :
        State(rule, sigmaSize, true),
        m_event_1(rule.getEventAt(0)),
        m_event_2(rule.getEventAt(1))
    {}

    std::vector<Event> Binary::getEvents() {
        return {m_event_1, m_event_2};
    }

    std::vector<u_int64_t> Binary::getEventNumericValues() {
        return {m_event_1.numericValue, m_event_2.numericValue};
    }

    bool Binary::isEqualTo(Binary &rule) {
        if (m_event_1.numericValue == rule.m_event_1.numericValue &&
        m_event_2.numericValue == rule.m_event_2.numericValue) {
            return true;
        }
        else {
            return false;
        }
    }

    Event Binary::getTarget() {
        return m_event_2;
    }
}

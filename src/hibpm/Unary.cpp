#include "Unary.hpp"

namespace hibpm
{
    Unary::Unary(size_t sigmaSize, Event &event) :
    Rule(sigmaSize, false),
    m_event(event)
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

    void Unary::print()
    {
        std::cout << m_ruleTypeString << "(" << m_event.name << ")" << std::endl;
    }
}
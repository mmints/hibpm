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

    bool Unary::eventsMatch(Rule &rule) {
        if (rule.isUnary())
        {
            auto unary = (Unary*) &rule;
            if (m_event.numericValue == unary->getEventNumericValue()) {
                return true;
            }
            else {
                return false;
            }
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
        std::cout << m_ruleTypeString << "(" << m_event.name << "(" << m_event.numericValue << ")" << ")" << std::endl;
    }
}
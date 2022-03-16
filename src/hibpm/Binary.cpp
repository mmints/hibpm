#include "Binary.hpp"

namespace hibpm
{
    Binary::Binary(size_t sigmaSize, std::vector<Event> &events) :
        Rule(sigmaSize, true),
        m_event_1(events.at(0)),
        m_event_2(events.at(1))
    {}

    std::vector<Event> Binary::getEvents() {
        return {m_event_1, m_event_2};
    }

    std::vector<u_int64_t> Binary::getEventNumericValues() {
        return {m_event_1.numericValue, m_event_2.numericValue};
    }

    bool Binary::eventsMatch(Rule &rule) {
        if (rule.isBinary())
        {
            auto binary = (Binary*) &rule;
            if (m_event_1.numericValue == binary->getEventNumericValues().at(0) &&
                m_event_2.numericValue == binary->getEventNumericValues().at(1)) {
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

    Event Binary::getTarget() {
        return m_event_2;
    }

    void Binary::print()
    {
        std::cout << m_ruleTypeString << "(" << m_event_1.name << "(" << m_event_1.numericValue << ")"
                    << ", " << m_event_2.name << "(" << m_event_2.numericValue << ")" << ")" << std::endl;
    }
}
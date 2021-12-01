#include "Rule.hpp"

namespace hibpm {

    hibpm::Rule::Rule(hibpm::RuleType type, std::vector<Event> events) :
            m_type{type},
            m_events{std::move(events)} {
        // Rule Type Sting for printing
        m_ruleType_str =
                {
                        // Unary Types
                        "PARTICIPATION",
                        "AT_MOST_ONE",
                        "INIT",
                        "END",

                        // Binary Types
                        "RESPONDED_EXISTENCE",
                        "RESPONSE",
                        "ALTERNATED_RESPONSE",
                        "CHAIN_RESPONSE",
                        "PRECEDENCE",
                        "ALTERNATED_PRECEDENCE",
                        "CHAIN_PRECEDENCE",
                        "CO_EXISTENCE",
                        "SUCCESSION",
                        "ALTERNATED_SUCCESSION",
                        "CHAIN_SUCCESSION",
                        "NOT_CHAIN_SUCCESSION",
                        "NOT_SUCCESSION",
                        "NOT_CO_EXISTENCE"
                };
    }

    std::string hibpm::Rule::toSting() {
        return m_ruleType_str[m_type];
    }

    RuleType Rule::getRuleType() {
        return m_type;
    }

    Event Rule::getEventAt(int index) {
        return m_events.at(index);
    }

}
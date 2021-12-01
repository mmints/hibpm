#pragma once

#include <vector>
#include <string>

namespace hibpm
{
    enum RuleType
    {
        // Unary Types
        PARTICIPATION,
        AT_MOST_ONE,
        INIT,
        END,

        // Binary Types
        RESPONDED_EXISTENCE,
        RESPONSE,
        ALTERNATED_RESPONSE,
        CHAIN_RESPONSE,
        PRECEDENCE,
        ALTERNATED_PRECEDENCE,
        CHAIN_PRECEDENCE,
        CO_EXISTENCE,
        SUCCESSION,
        ALTERNATED_SUCCESSION,
        CHAIN_SUCCESSION,
        NOT_CHAIN_SUCCESSION,
        NOT_SUCCESSION,
        NOT_CO_EXISTENCE
    };

    struct Event
    {
        std::string name;
        u_int64_t numericValue; // checking against vector length -> size_t, which is unsigned long long
    };

    ///// Rule Class /////

    class Rule
    {
    private:
        RuleType m_type;
        std::vector<Event> m_events;

        std::vector<std::string> m_ruleType_str;

    public:
        Rule(RuleType type,std::vector<Event> events);

        RuleType getRuleType();
        Event getEventAt(int index);
        std::string toSting();
    };
}
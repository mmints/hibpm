#pragma once

#include <vector>

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

    class Rule
    {
    private:
        RuleType type;
        std::vector<Event> events;

        const std::vector<std::string> ruleType_str =
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

    public:
        std::string toSting() {
            return ruleType_str[type];
        }
    };
}
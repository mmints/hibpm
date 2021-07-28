#ifndef HIBPM_DECLARE_H
#define HIBPM_DECLARE_H

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

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
    };

    struct Rule
    {
        RuleType type;
        std::vector<Event> events;
    };

    // This Class is an object representation of DECLARE
    class Declare
    {
    public:
        Declare();
        ~Declare() = default;

        void addRule(const Rule& rule);
        void addRule(RuleType type, std::string event_val);
        void addRule(RuleType type, std::string event_val_1, std::string event_val_2);

        std::vector<Rule> getRules();
        std::vector<Event> getEvents();

    private:
        std::vector<Event> m_events;
        std::vector<Rule> m_rules;

        bool checkEventExistence(const Event& event);
    };
}

#endif //HIBPM_DECLARE_H

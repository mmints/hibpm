#pragma once

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
        u_int64_t numericValue; // checking against vector length -> size_t, which is unsigned long long
    };

    struct Rule
    {
        RuleType type;
        std::vector<Event> events;



        bool isEqualTo(Rule r2){
            if (type == r2.type &&
                events[0].numericValue == r2.events[0].numericValue){
                if (type == RuleType::END ||
                    type == RuleType::INIT ||
                    type == RuleType::AT_MOST_ONE ||
                    type == RuleType::PARTICIPATION){
                    return true;
                }else if (events[1].numericValue == r2.events[1].numericValue){
                    return true;
                }

            }

            return false;
        }

        Event getTarget(){
            if (type == RuleType::END ||
                type == RuleType::INIT ||
                type == RuleType::AT_MOST_ONE ||
                type == RuleType::PARTICIPATION){
                return events[0];
            }else{
                return events[1];
            }
        }

        bool isUnary(){
            if (type == RuleType::END ||
                type == RuleType::INIT ||
                type == RuleType::AT_MOST_ONE ||
                type == RuleType::PARTICIPATION){
                return true;
            }
            return false;
        }
    };

    // This Class is an object representation of DECLARE
    class Declare
    {
    public:
        Declare();
        ~Declare() = default;

        // This is used in declare.yy
        void addRule(RuleType type, const std::string& event_val);
        void addRule(RuleType type, const std::string& event_val_1, const std::string& event_val_2);

        std::vector<Rule> getRules();
        std::vector<Event> getEvents();

    private:
        std::vector<Event> m_events;
        std::vector<Rule> m_rules;

        void addRuleAndEventsToSet(RuleType type, const std::vector<std::string>& event_names);
        bool checkEventExistence(const std::string &event_name);
        u_int64_t eventNameToNumericValue(const std::string &event_name);
    };
}
#pragma once

#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include <memory>
#include <list>

#include "Rule.hpp"


namespace hibpm
{
    // This Class is an object representation of DECLARE
    class Declare
    {
    public:
        Declare();
        ~Declare() = default;

        // This is used in declare.yy
        void addUnaryRule(RuleType type, const std::string& event_val);
        void addBinaryRule(RuleType type, const std::string& event_val_1, const std::string& event_val_2);

        std::vector<Rule> getRules();
        std::vector<Event> getEvents();
        u_int64_t getSigmaSize();

    private:
        std::vector<Event> m_events;
        std::list<std::shared_ptr<Rule>> m_rules;

        void addRuleAndEventsToSet(RuleType type, const std::vector<std::string>& event_names);
        bool checkEventExistence(const std::string &event_name);
        u_int64_t eventNameToNumericValue(const std::string &event_name);
    };
}
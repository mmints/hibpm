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
    class DeclareContext
    {
    public:
        struct EventData
        {
            std::string name;
            u_int64_t numericValue; // checking against vector length -> size_t, which is unsigned long long
        };

        struct RuleData
        {
            RuleType type;
            std::vector<EventData> events;
        };

        DeclareContext();
        ~DeclareContext() = default;

        // This is used in declare.yy
        void addUnaryRuleData(RuleType type, const std::string& event_val);
        void addBinaryRuleData(RuleType type, const std::string& event_val_1, const std::string& event_val_2);

        std::vector<RuleData> getRuleData();
        std::vector<EventData> getEventData();
        u_int64_t getSigmaSize();

    private:
        std::vector<EventData> m_eventData;
        std::vector<RuleData> m_ruleData;

        void addRuleDataAndEventDataToSet(RuleType type, const std::vector<std::string>& event_names);
        bool checkEventDataExistence(const std::string &event_name);
        u_int64_t eventNameToNumericValue(const std::string &event_name);
    };
}
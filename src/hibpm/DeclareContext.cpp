#include "DeclareContext.hpp"

namespace hibpm {

    DeclareContext::DeclareContext() :
            m_eventData{},
            m_ruleData{}
    {}

    void DeclareContext::addUnaryRuleData(RuleType type, const std::string& event_val) {
        std::vector<std::string> event_val_in_vec;
        event_val_in_vec.push_back(event_val);
        addRuleDataAndEventDataToSet(type, event_val_in_vec);
    }

    void DeclareContext::addBinaryRuleData(RuleType type, const std::string& event_val_1, const std::string& event_val_2) {
        std::vector<std::string> event_val_in_vec;
        event_val_in_vec.push_back(event_val_1);
        event_val_in_vec.push_back(event_val_2);
        addRuleDataAndEventDataToSet(type, event_val_in_vec);
    }

    std::vector<DeclareContext::RuleData> DeclareContext::getRuleData() {
        return m_ruleData;
    }

    std::vector<DeclareContext::EventData> DeclareContext::getEventData() {
        return m_eventData;
    }

    u_int64_t DeclareContext::getSigmaSize() {
        return m_eventData.size();
    }

    void DeclareContext::addRuleDataAndEventDataToSet(RuleType type, const std::vector<std::string>& event_names) {

        std::vector<DeclareContext::EventData> rule_events;

        for (auto& event_name : event_names)
        {
            // First check if the used event in a rule are already in the
            if (! hibpm::DeclareContext::checkEventDataExistence(event_name))
            {
                DeclareContext::EventData event {event_name, m_eventData.size()};
                rule_events.push_back(event);
                m_eventData.push_back(event); // And if not, add them to it
            }
            else {
                DeclareContext::EventData event {event_name, eventNameToNumericValue(event_name)};
                rule_events.push_back(event);
            }
        }
        DeclareContext::RuleData ruleData{type, rule_events};
        m_ruleData.push_back(ruleData);
    }

    bool DeclareContext::checkEventDataExistence(const std::string &event_name) {
        // Check if the given even is already added to the event pool
        if (m_eventData.empty())
            return false;

        for (const auto& e : m_eventData)
            if (e.name == event_name)
                return true;

        return false;
    }

    u_int64_t DeclareContext::eventNameToNumericValue(const std::string &event_name) {
        for (u_int64_t i = 0; i < m_eventData.size(); i++) {
            if (event_name == m_eventData[i].name)
            {
                return i;
            }
        }
        return 0;
    }
}

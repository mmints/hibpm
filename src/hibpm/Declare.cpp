#include "Declare.hpp"

namespace hibpm {

    Declare::Declare() :
            m_events{},
            m_rules{}
    {}

    void Declare::addUnaryRule(RuleType type, const std::string& event_val) {
        // TODO: Check if the incoming type is unary -> Actually, this is handles in Bison
        std::vector<std::string> event_val_in_vec;
        event_val_in_vec.push_back(event_val);
        addRuleAndEventsToSet(type, event_val_in_vec);
    }

    void Declare::addBinaryRule(RuleType type, const std::string& event_val_1, const std::string& event_val_2) {
        // TODO: Check if the incoming type is unary -> Actually, this is handles in Bison
        std::vector<std::string> event_val_in_vec;
        event_val_in_vec.push_back(event_val_1);
        event_val_in_vec.push_back(event_val_2);
        addRuleAndEventsToSet(type, event_val_in_vec);
    }

    std::vector<Rule> Declare::getRules() {
        return m_rules;
    }

    std::vector<Event> Declare::getEvents() {
        return m_events;
    }

    u_int64_t Declare::getSigmaSize() {
        return m_events.size();
    }

    void Declare::addRuleAndEventsToSet(RuleType type, const std::vector<std::string>& event_names) {

        std::vector<Event> rule_events;

        for (auto& event_name : event_names)
        {
            // First check if the used event in a rule are already in the
            if (! hibpm::Declare::checkEventExistence(event_name))
            {
                Event event {event_name, m_events.size()};
                rule_events.push_back(event);
                m_events.push_back(event); // And if not, add them to it
            }
            else {
                Event event {event_name, eventNameToNumericValue(event_name)};
                rule_events.push_back(event);
            }
        }
        Rule rule(type, rule_events);
        m_rules.push_back(rule);
    }

    bool Declare::checkEventExistence(const std::string &event_name) {
        // Check if the given even is already added to the event pool

        if (m_events.empty())
            return false;

        for (const auto& e : m_events)
            if (e.name == event_name)
                return true;

        return false;
    }

    u_int64_t Declare::eventNameToNumericValue(const std::string &event_name) {
        // TODO: Optimize. This is quick and dirty implementation
        for (u_int64_t i = 0; i < m_events.size(); i++) {
            if (event_name == m_events[i].name)
            {
                return i;
            }
        }
        return 0;
    }
}

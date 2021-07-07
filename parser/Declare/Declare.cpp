#include "Declare.hpp"
#include "iostream"

namespace hibpm {

    Declare::Declare() :
            m_events{},
            m_rules{}
    {}

    void Declare::addRule(const Rule &rule) {
        m_rules.push_back(rule);

        for (const auto& event : rule.events)
        {
            // First check if the used event in a rule are already in the
            if (! hibpm::Declare::checkEventExistence(event)) {
                m_events.push_back(event); // And if not, add them to it
            }
        }
    }

    void Declare::addRule(RuleType type, std::string event_val) {
        // TODO: Check if the incoming type is unary
        Event event {event_val};
        Rule rule {type, std::vector<Event>{event}};
        addRule(rule);
    }

    void Declare::addRule(RuleType type, std::string event_val_1, std::string event_val_2) {
        // TODO: Check if the incoming type is unary
        Event event_1 {event_val_1};
        Event event_2 {event_val_2};
        Rule rule {type, std::vector<Event>{event_1, event_2}};
        addRule(rule);
    }

    std::vector<Rule> Declare::getRules() {
        return m_rules;
    }

    std::vector<Event> Declare::getEvents() {
        return m_events;
    }

    bool Declare::checkEventExistence(const Event &event) {
        // Check if the given even is already added to the event pool

        if (m_events.empty())
            return false;

        for (const auto& e : m_events)
            if (e.name == event.name)
                return true;

        return false;
    }
}
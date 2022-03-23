#include "DeclareContext.hpp"

namespace hibpm {

    DeclareContext::DeclareContext() :
            m_eventData{},
            m_constraintData{}
    {}

    void DeclareContext::addUnaryConstraintData(ConstraintType type, const std::string& event_val) {
        std::vector<std::string> event_val_in_vec;
        event_val_in_vec.push_back(event_val);
        addConstraintDataAndEventDataToSet(type, event_val_in_vec);
    }

    void DeclareContext::addBinaryConstraintData(ConstraintType type, const std::string& activation_val, const std::string& target_val) {
        std::vector<std::string> event_val_in_vec;
        event_val_in_vec.push_back(activation_val);
        event_val_in_vec.push_back(target_val);
        addConstraintDataAndEventDataToSet(type, event_val_in_vec);
    }

    std::vector<DeclareContext::ConstraintData> DeclareContext::getConstraintData() {
        return m_constraintData;
    }

    std::vector<Event> DeclareContext::getEventData() {
        return m_eventData;
    }

    u_int64_t DeclareContext::getEventDataCount() {
        return m_eventData.size();
    }

    void DeclareContext::addConstraintDataAndEventDataToSet(ConstraintType type, const std::vector<std::string>& event_names) {

        std::vector<Event> constraint_events;

        for (auto& event_name : event_names)
        {
            // First check if the used event in a constraint are already in the
            if (! hibpm::DeclareContext::checkEventDataExistence(event_name))
            {
                Event event {event_name, m_eventData.size()};
                constraint_events.push_back(event);
                m_eventData.push_back(event); // And if not, add them to it
            }
            else {
                Event event {event_name, eventNameToNumericValue(event_name)};
                constraint_events.push_back(event);
            }
        }
        DeclareContext::ConstraintData constraintData{type, constraint_events};
        m_constraintData.push_back(constraintData);
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

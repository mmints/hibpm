#include "Process.hpp"

namespace hibpm {

    Process::Process(hibpm::Declare &declare_kb) {
        createAllStates(declare_kb);
    }

    void Process::createAllStates(Declare &declare_kb) {
        for (Rule &rule : declare_kb.getRules()) {
            m_states.push_back(createState(rule.type, rule.events, declare_kb.getEvents().size()));
        }
    }

    std::vector<State> Process::getStates() {
        return m_states;
    }

    State Process::createState(RuleType type, vector<Event> &events, size_t sigma_size) {
        switch (type)
        {
            // Unary
            case PARTICIPATION:
                return participation(sigma_size, events[0].numericValue);
            case AT_MOST_ONE:
                return atMostOne(sigma_size, events[0].numericValue);
            case INIT:
                return init(sigma_size, events[0].numericValue);
            case END:
                return end(sigma_size, events[0].numericValue);

                // Binary
            case RESPONDED_EXISTENCE:
                return respondedExistence(sigma_size, events[0].numericValue, events[1].numericValue);
            case RESPONSE:
                return response(sigma_size, events[0].numericValue, events[1].numericValue);
            case ALTERNATED_RESPONSE:
                return alternatedResponse(sigma_size, events[0].numericValue, events[1].numericValue);
            case CHAIN_RESPONSE:
                return chainResponse(sigma_size, events[0].numericValue, events[1].numericValue);
            case PRECEDENCE:
                return precedence(sigma_size, events[0].numericValue, events[1].numericValue);
            case ALTERNATED_PRECEDENCE:
                return alternatedPrecedence(sigma_size, events[0].numericValue, events[1].numericValue);
            case CHAIN_PRECEDENCE:
                return chainPrecedence(sigma_size, events[0].numericValue, events[1].numericValue);
            case CO_EXISTENCE:
                return coExistence(sigma_size, events[0].numericValue, events[1].numericValue);
            case SUCCESSION:
                return succession(sigma_size, events[0].numericValue, events[1].numericValue);
            case ALTERNATED_SUCCESSION:
                return alternateSuccession(sigma_size, events[0].numericValue, events[1].numericValue);
            case CHAIN_SUCCESSION:
                return chainSuccession(sigma_size, events[0].numericValue, events[1].numericValue);
            case NOT_CHAIN_SUCCESSION:
                return notChainSuccession(sigma_size, events[0].numericValue, events[1].numericValue);
            case NOT_SUCCESSION:
                return notSuccession(sigma_size, events[0].numericValue, events[1].numericValue);
            case NOT_CO_EXISTENCE:
                return notCoExistence(sigma_size, events[0].numericValue, events[1].numericValue);
        }
    }

    // Unary States

    Participation Process::participation(size_t sigma_size, u_int64_t event_value) {
        // TODO: Implement Automaton
        Automaton automaton(0,0);
        return {PARTICIPATION, sigma_size, automaton, event_value};
    }

    AtMostOne Process::atMostOne(size_t sigma_size, u_int64_t event_value) {
        // TODO: Implement Automaton
        Automaton automaton(0,0);
        return {AT_MOST_ONE, sigma_size, automaton, event_value};
    }

    Init Process::init(size_t sigma_size, u_int64_t event_value) {
        // TODO: Implement Automaton
        Automaton automaton(0,0);
        return {INIT, sigma_size, automaton, event_value};
    }

    End Process::end(size_t sigma_size, u_int64_t event_value) {
        // TODO: Implement Automaton
        Automaton automaton(0,0);
        return {END, sigma_size, automaton, event_value};
    }

    // Binary States

    RespondedExistence Process::respondedExistence(size_t sigma_size, u_int64_t event_value_1, u_int64_t event_value_2) {
        // TODO: Implement Automaton
        Automaton automaton(0,0);
        return {RESPONDED_EXISTENCE, sigma_size, automaton, event_value_1, event_value_2};
    }

    Response Process::response(size_t sigma_size, u_int64_t event_value_1, u_int64_t event_value_2) {
        // TODO: Implement Automaton
        Automaton automaton(0,0);
        return {RESPONSE, sigma_size, automaton, event_value_1, event_value_2};
    }

    AlternatedResponse Process::alternatedResponse(size_t sigma_size, u_int64_t event_value_1, u_int64_t event_value_2) {
        // TODO: Implement Automaton
        Automaton automaton(0,0);
        return {ALTERNATED_RESPONSE, sigma_size, automaton, event_value_1, event_value_2};
    }

    ChainResponse Process::chainResponse(size_t sigma_size, u_int64_t event_value_1, u_int64_t event_value_2) {
        // TODO: Implement Automaton
        Automaton automaton(0,0);
        return {CHAIN_RESPONSE, sigma_size, automaton, event_value_1, event_value_2};
    }

    Precedence Process::precedence(size_t sigma_size, u_int64_t event_value_1, u_int64_t event_value_2) {
        // TODO: Implement Automaton
        Automaton automaton(0,0);
        return {PRECEDENCE, sigma_size, automaton, event_value_1, event_value_2};
    }

    AlternatedPrecedence Process::alternatedPrecedence(size_t sigma_size, u_int64_t event_value_1, u_int64_t event_value_2) {
        // TODO: Implement Automaton
        Automaton automaton(0,0);
        return {ALTERNATED_PRECEDENCE, sigma_size, automaton, event_value_1, event_value_2};
    }

    ChainPrecedence Process::chainPrecedence(size_t sigma_size, u_int64_t event_value_1, u_int64_t event_value_2) {
        // TODO: Implement Automaton
        Automaton automaton(0,0);
        return {CHAIN_PRECEDENCE, sigma_size, automaton, event_value_1, event_value_2};
    }

    CoExistence Process::coExistence(size_t sigma_size, u_int64_t event_value_1, u_int64_t event_value_2) {
        // TODO: Implement Automaton
        Automaton automaton(0,0);
        return {CO_EXISTENCE, sigma_size, automaton, event_value_1, event_value_2};
    }

    Succession Process::succession(size_t sigma_size, u_int64_t event_value_1, u_int64_t event_value_2) {
        // TODO: Implement Automaton
        Automaton automaton(0,0);
        return {SUCCESSION, sigma_size, automaton, event_value_1, event_value_2};
    }

    AlternateSuccession Process::alternateSuccession(size_t sigma_size, u_int64_t event_value_1, u_int64_t event_value_2) {
        // TODO: Implement Automaton
        Automaton automaton(0,0);
        return {ALTERNATED_SUCCESSION, sigma_size, automaton, event_value_1, event_value_2};
    }

    ChainSuccession Process::chainSuccession(size_t sigma_size, u_int64_t event_value_1, u_int64_t event_value_2) {
        // TODO: Implement Automaton
        Automaton automaton(0,0);
        return {CHAIN_SUCCESSION, sigma_size, automaton, event_value_1, event_value_2};
    }

    NotChainSuccession Process::notChainSuccession(size_t sigma_size, u_int64_t event_value_1, u_int64_t event_value_2) {
        // TODO: Implement Automaton
        Automaton automaton(0,0);
        return {NOT_CHAIN_SUCCESSION, sigma_size, automaton, event_value_1, event_value_2};
    }

    NotSuccession Process::notSuccession(size_t sigma_size, u_int64_t event_value_1, u_int64_t event_value_2) {
        // TODO: Implement Automaton
        Automaton automaton(0,0);
        return {NOT_SUCCESSION, sigma_size, automaton, event_value_1, event_value_2};
    }

    NotCoExistence Process::notCoExistence(size_t sigma_size, u_int64_t event_value_1, u_int64_t event_value_2) {
        // TODO: Implement Automaton
        Automaton automaton(0,0);
        return {NOT_CO_EXISTENCE, sigma_size, automaton, event_value_1, event_value_2};
    }
}

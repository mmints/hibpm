#pragma once

#include "Automaton/Automaton.hpp"
#include "Declare/Declare.hpp"
#include "State.hpp"

namespace hibpm
{
    class Process
    {
    public:
        explicit Process(Declare &declare_kb);
        std::vector<State> getStates();

    private:
        std::vector<State> m_states;

        void createAllStates(Declare &declare_kb);
        State createState(RuleType type, vector<Event> &events, size_t sigma_size);

        // Unary Rule Automata
        Participation participation(size_t sigma_size, u_int64_t event_value);
        AtMostOne atMostOne(size_t sigma_size, u_int64_t event_value);
        Init init(size_t sigma_size, u_int64_t event_value);
        End end(size_t sigma_size, u_int64_t event_value);

        // Binary Rule Automata
        RespondedExistence respondedExistence(size_t sigma_size, u_int64_t event_value_1, u_int64_t event_value_2);
        Response response(size_t sigma_size, u_int64_t event_value_1, u_int64_t event_value_2);
        AlternatedResponse alternatedResponse(size_t sigma_size, u_int64_t event_value_1, u_int64_t event_value_2);
        ChainResponse chainResponse(size_t sigma_size, u_int64_t event_value_1, u_int64_t event_value_2);
        Precedence precedence(size_t sigma_size, u_int64_t event_value_1, u_int64_t event_value_2);
        AlternatedPrecedence alternatedPrecedence(size_t sigma_size, u_int64_t event_value_1, u_int64_t event_value_2);
        ChainPrecedence chainPrecedence(size_t sigma_size, u_int64_t event_value_1, u_int64_t event_value_2);
        CoExistence coExistence(size_t sigma_size, u_int64_t event_value_1, u_int64_t event_value_2);
        Succession succession(size_t sigma_size, u_int64_t event_value_1, u_int64_t event_value_2);
        AlternateSuccession alternateSuccession(size_t sigma_size, u_int64_t event_value_1, u_int64_t event_value_2);
        ChainSuccession chainSuccession(size_t sigma_size, u_int64_t event_value_1, u_int64_t event_value_2);
        NotChainSuccession notChainSuccession(size_t sigma_size, u_int64_t event_value_1, u_int64_t event_value_2);
        NotSuccession notSuccession(size_t sigma_size, u_int64_t event_value_1, u_int64_t event_value_2);
        NotCoExistence notCoExistence(size_t sigma_size, u_int64_t event_value_1, u_int64_t event_value_2);
    };
}


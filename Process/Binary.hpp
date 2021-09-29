#pragma once

#include "State.hpp"

namespace hibpm
{
    // Overall abstract Class for Binary State Definitions
    class Binary : public State
    {
    public:
        Binary(Rule &rule, size_t sigmaSize);

        std::vector<Event> getEvents();
        std::vector<u_int64_t> getEventNumericValues();

    private:
        // Get the events from the given rule in constructor
        Event m_event_1;
        Event m_event_2;
    };

    class RespondedExistence : Binary {};
    class Response : Binary {};
    class AlternatedResponse : Binary {};
    class ChainResponse : Binary {};
    class Precedence : Binary {};
    class AlternatedPrecedence : Binary {};
    class ChainPrecedence : Binary {};
    class CoExistence : Binary {};
    class Succession : Binary {};
    class AlternateSuccession : Binary {};
    class ChainSuccession : Binary {};
    class NotChainSuccession : Binary {};
    class NotSuccession : Binary {};
    class NotCoExistence : Binary {};
}

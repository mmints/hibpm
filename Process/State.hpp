#pragma once

#include <vector>

#include "Automaton/Automaton.hpp"
#include "Declare/Declare.hpp"

namespace hibpm
{
    class State
    {
    public:
        State(Rule &rule, size_t sigmaSize);

        Rule getRule();
        RuleType getRuleType();
        Automaton getAutomata();

    private:
        Rule m_rule;
        size_t m_sigmaSize;
        Automaton m_automaton;
    };

    class Unary : State
    {
    public:
        Unary(Rule &rule, size_t sigmaSize);

        Event getEvent();
        u_int64_t getEventNumericValue();

    private:
        Event m_event;
    };

    class Binary : State
    {
    public:
        Binary(Rule &rule, size_t sigmaSize);

        std::vector<Event> getEvents();
        std::vector<u_int64_t> getEventNumericValues();

    private:
        Event m_event_1;
        Event m_event_2;
    };

    // Unary
    class Participation : Unary{
    public:
        Participation(Rule &rule, size_t sigmaSize) :
        Unary(rule, sigmaSize)
        {}
    };
    class AtMostOne : Unary {
        AtMostOne(Rule &rule, size_t sigmaSize) :
        Unary(rule, sigmaSize)
        {}
    };
    class Init : Unary {
        Init(Rule &rule, size_t sigmaSize) :
        Unary(rule, sigmaSize)
        {}
    };
    class End : Unary {
        End(Rule &rule, size_t sigmaSize) :
        Unary(rule, sigmaSize)
        {}
    };

    // Binary
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

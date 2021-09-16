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

    protected:
        Rule m_rule;
        size_t m_sigmaSize;
        Automaton m_automaton;

        virtual void initializeAutomaton() = 0;
    };

    class Unary : public State
    {
    public:
        Unary(Rule &rule, size_t sigmaSize);

        Event getEvent();
        u_int64_t getEventNumericValue();

    protected:
        Event m_event;
    };

    class Binary : public State
    {
    public:
        Binary(Rule &rule, size_t sigmaSize);

        std::vector<Event> getEvents();
        std::vector<u_int64_t> getEventNumericValues();

    protected:
        Event m_event_1;
        Event m_event_2;
    };

    // Unary
    class Participation : public Unary{
    public:
        Participation(Rule &rule, size_t sigmaSize);
    private:
        void initializeAutomaton() override;
    };

    class AtMostOne : public Unary {
    public:
        AtMostOne(Rule &rule, size_t sigmaSize);

    private:
        void initializeAutomaton() override;
    };

    class Init : public Unary {
    public:
        Init(Rule &rule, size_t sigmaSize);
    private:
        void initializeAutomaton() override;
    };

    class End : public Unary {
    public:
        End(Rule &rule, size_t sigmaSize);

    private:
        void initializeAutomaton() override;
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

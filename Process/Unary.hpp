#pragma once

#include "State.hpp"

namespace hibpm
{
    // Overall abstract Class for Unary State Definitions
    class Unary : public State
    {
    public:
        Unary(Rule &rule, size_t sigmaSize);

        Event getEvent();
        u_int64_t getEventNumericValue();
        bool isEqualTo(Unary &rule);
        Event getTarget();

    protected:
        Event m_event; // Get the event from the given rule in constructor
    };

    class Participation : public Unary {
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
}

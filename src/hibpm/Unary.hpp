#pragma once

#include "Constraint.hpp"

namespace hibpm
{
    // Overall abstract Class for Unary State Definitions
    class Unary : public Constraint
    {
    public:
        Unary(size_t sigmaSize, Event &event);

        Event getEvent();
        u_int64_t getEventNumericValue();
        Event getTarget();
        bool eventsMatch(Constraint &rule) override;
        void print() override;

    protected:
        Event m_event;
    };

    class Participation : public Unary {
    public:
        Participation(size_t sigmaSize, Event &event);
    private:
        void initializeAutomaton() override;
    };

    class AtMostOne : public Unary {
    public:
        AtMostOne(size_t sigmaSize, Event &event);
    private:
        void initializeAutomaton() override;
    };

    class AtMostTwo : public Unary {
    public:
        AtMostTwo(size_t sigmaSize, Event &event);
    private:
        void initializeAutomaton() override;
    };

    class AtMostThree : public Unary {
    public:
        AtMostThree(size_t sigmaSize, Event &event);
    private:
        void initializeAutomaton() override;
    };

    class AtLeastOne : public Unary {
    public:
        AtLeastOne(size_t sigmaSize, Event &event);
    private:
        void initializeAutomaton() override;
    };

    class Init : public Unary {
    public:
        Init(size_t sigmaSize, Event &event);
    private:
        void initializeAutomaton() override;
    };

    class End : public Unary {
    public:
        End(size_t sigmaSize, Event &event);
    private:
        void initializeAutomaton() override;
    };
}

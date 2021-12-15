#pragma once

#include "State.hpp"

namespace hibpm
{
    // Overall abstract Class for Unary State Definitions
    class Unary : public Rule
    {
    public:
        Unary(size_t sigmaSize, Event &event);

        Event getEvent();
        u_int64_t getEventNumericValue();
        bool isEqualTo(Unary &rule);
        Event getTarget();

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

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

    class RespondedExistence : Binary {
    public:
        RespondedExistence(Rule &rule, size_t sigmaSize);
    private:
        void initializeAutomaton() override;
    };

    class Response : Binary {
    public:
        Response(Rule &rule, size_t sigmaSize);
    private:
        void initializeAutomaton() override;
    };

    class AlternatedResponse : Binary {
    public:
        AlternatedResponse(Rule &rule, size_t sigmaSize);
    private:
        void initializeAutomaton() override;
    };

    class ChainResponse : Binary {
    public:
        ChainResponse(Rule &rule, size_t sigmaSize);
    private:
        void initializeAutomaton() override;
    };

    class Precedence : Binary {
    public:
        Precedence(Rule &rule, size_t sigmaSize);
    private:
        void initializeAutomaton() override;
    };

    class AlternatedPrecedence : Binary {
    public:
        AlternatedPrecedence(Rule &rule, size_t sigmaSize);
    private:
        void initializeAutomaton() override;
    };

    class ChainPrecedence : Binary {
    public:
        ChainPrecedence(Rule &rule, size_t sigmaSize);
    private:
        void initializeAutomaton() override;
    };

    class CoExistence : Binary {
    public:
        CoExistence(Rule &rule, size_t sigmaSize);
    private:
        void initializeAutomaton() override;
    };

    class Succession : Binary {
    public:
        Succession(Rule &rule, size_t sigmaSize);
    private:
        void initializeAutomaton() override;
    };

    class AlternateSuccession : Binary {
    public:
        AlternateSuccession(Rule &rule, size_t sigmaSize);
    private:
        void initializeAutomaton() override;
    };

    class ChainSuccession : Binary {
    public:
        ChainSuccession(Rule &rule, size_t sigmaSize);
    private:
        void initializeAutomaton() override;
    };

    class NotChainSuccession : Binary {
    public:
        NotChainSuccession(Rule &rule, size_t sigmaSize);
    private:
        void initializeAutomaton() override;
    };

    class NotSuccession : Binary {
    public:
        NotSuccession(Rule &rule, size_t sigmaSize);
    private:
        void initializeAutomaton() override;
    };

    class NotCoExistence : Binary {
    public:
        NotCoExistence(Rule &rule, size_t sigmaSize);
    private:
        void initializeAutomaton() override;
    };
}

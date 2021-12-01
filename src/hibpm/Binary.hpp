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
        bool isEqualTo(Binary &rule);
        Event getTarget();


    protected:
        // Get the events from the given rule in constructor
        Event m_event_1;
        Event m_event_2;
    };

    class RespondedExistence : public Binary {
    public:
        RespondedExistence(Rule &rule, size_t sigmaSize);
    private:
        void initializeAutomaton() override;
    };

    class Response : public Binary {
    public:
        Response(Rule &rule, size_t sigmaSize);
    private:
        void initializeAutomaton() override;
    };

    class AlternatedResponse : public Binary {
    public:
        AlternatedResponse(Rule &rule, size_t sigmaSize);
    private:
        void initializeAutomaton() override;
    };

    class ChainResponse : public Binary {
    public:
        ChainResponse(Rule &rule, size_t sigmaSize);
    private:
        void initializeAutomaton() override;
    };

    class Precedence : public Binary {
    public:
        Precedence(Rule &rule, size_t sigmaSize);
    private:
        void initializeAutomaton() override;
    };

    class AlternatedPrecedence : public Binary {
    public:
        AlternatedPrecedence(Rule &rule, size_t sigmaSize);
    private:
        void initializeAutomaton() override;
    };

    class ChainPrecedence : public Binary {
    public:
        ChainPrecedence(Rule &rule, size_t sigmaSize);
    private:
        void initializeAutomaton() override;
    };

    class CoExistence : public Binary {
    public:
        CoExistence(Rule &rule, size_t sigmaSize);
    private:
        void initializeAutomaton() override;
    };

    class Succession : public Binary {
    public:
        Succession(Rule &rule, size_t sigmaSize);
    private:
        void initializeAutomaton() override;
    };

    class AlternateSuccession : public Binary {
    public:
        AlternateSuccession(Rule &rule, size_t sigmaSize);
    private:
        void initializeAutomaton() override;
    };

    class ChainSuccession : public Binary {
    public:
        ChainSuccession(Rule &rule, size_t sigmaSize);
    private:
        void initializeAutomaton() override;
    };

    class NotChainSuccession : public Binary {
    public:
        NotChainSuccession(Rule &rule, size_t sigmaSize);
    private:
        void initializeAutomaton() override;
    };

    class NotSuccession : public Binary {
    public:
        NotSuccession(Rule &rule, size_t sigmaSize);
    private:
        void initializeAutomaton() override;
    };

    class NotCoExistence : public Binary {
    public:
        NotCoExistence(Rule &rule, size_t sigmaSize);
    private:
        void initializeAutomaton() override;
    };
}

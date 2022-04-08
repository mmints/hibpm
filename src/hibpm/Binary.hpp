#pragma once

#include "Constraint.hpp"

namespace hibpm
{
    // Overall abstract Class for Binary State Definitions
    class Binary : public Constraint
    {
    public:
        Binary(size_t sigmaSize, std::vector<Event> &events);

        std::vector<Event> getEvents();
        std::vector<u_int64_t> getEventNumericValues();
        bool eventsMatch(Constraint &rule) override;
        Event getTarget();

        std::string print() override;

    protected:
        // Get the events from the given rule in constructor
        Event m_activation;
        Event m_target;
    };

    class RespondedExistence : public Binary {
    public:
        RespondedExistence(size_t sigmaSize, std::vector<Event> &events);
    private:
        void initializeAutomaton() override;
    };

    class Response : public Binary {
    public:
        Response(size_t sigmaSize, std::vector<Event> &events);
    private:
        void initializeAutomaton() override;
    };

    class AlternatedResponse : public Binary {
    public:
        AlternatedResponse(size_t sigmaSize, std::vector<Event> &events);
    private:
        void initializeAutomaton() override;
    };

    class ChainResponse : public Binary {
    public:
        ChainResponse(size_t sigmaSize, std::vector<Event> &events);
    private:
        void initializeAutomaton() override;
    };

    class Precedence : public Binary {
    public:
        Precedence(size_t sigmaSize, std::vector<Event> &events);
    private:
        void initializeAutomaton() override;
    };

    class AlternatedPrecedence : public Binary {
    public:
        AlternatedPrecedence(size_t sigmaSize, std::vector<Event> &events);
    private:
        void initializeAutomaton() override;
    };

    class ChainPrecedence : public Binary {
    public:
        ChainPrecedence(size_t sigmaSize, std::vector<Event> &events);
    private:
        void initializeAutomaton() override;
    };

    class CoExistence : public Binary {
    public:
        CoExistence(size_t sigmaSize, std::vector<Event> &events);
    private:
        void initializeAutomaton() override;
    };

    class Succession : public Binary {
    public:
        Succession(size_t sigmaSize, std::vector<Event> &events);
    private:
        void initializeAutomaton() override;
    };

    class AlternateSuccession : public Binary {
    public:
        AlternateSuccession(size_t sigmaSize, std::vector<Event> &events);
    private:
        void initializeAutomaton() override;
    };

    class ChainSuccession : public Binary {
    public:
        ChainSuccession(size_t sigmaSize, std::vector<Event> &events);
    private:
        void initializeAutomaton() override;
    };

    class NotChainSuccession : public Binary {
    public:
        NotChainSuccession(size_t sigmaSize, std::vector<Event> &events);
    private:
        void initializeAutomaton() override;
    };

    class NotSuccession : public Binary {
    public:
        NotSuccession(size_t sigmaSize, std::vector<Event> &events);
    private:
        void initializeAutomaton() override;
    };

    class NotCoExistence : public Binary {
    public:
        NotCoExistence(size_t sigmaSize, std::vector<Event> &events);
    private:
        void initializeAutomaton() override;
    };
}

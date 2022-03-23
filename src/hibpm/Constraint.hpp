#pragma once

#include <vector>
#include <string>

#include "Automaton.hpp"

namespace hibpm
{
    enum RuleType
    {
        // Unary Types
        PARTICIPATION,
        AT_MOST_ONE,
        INIT,
        END,

        // Binary Types
        RESPONDED_EXISTENCE,
        RESPONSE,
        ALTERNATED_RESPONSE,
        CHAIN_RESPONSE,
        PRECEDENCE,
        ALTERNATED_PRECEDENCE,
        CHAIN_PRECEDENCE,
        CO_EXISTENCE,
        SUCCESSION,
        ALTERNATED_SUCCESSION,
        CHAIN_SUCCESSION,
        NOT_CHAIN_SUCCESSION,
        NOT_SUCCESSION,
        NOT_CO_EXISTENCE
    };

    struct Event
    {
        std::string name;
        u_int64_t numericValue; // checking against vector length -> size_t, which is unsigned long long
    };

    ///// Abstract Rule Class /////

    class Constraint
    {
    public:
        Constraint(size_t sigmaSize, bool isBinary);

        bool isBinary();
        bool isUnary();
        Automaton getAutomata();
        RuleType getType();
        std::string getTypeString();

        virtual bool eventsMatch(Constraint &rule) = 0;

        virtual void print() = 0;

    protected:
        RuleType m_type;
        std::string m_ruleTypeString;
        size_t m_sigmaSize;
        bool m_isBinary;
        Automaton m_automaton;

        virtual void initializeAutomaton() = 0;
    };
}
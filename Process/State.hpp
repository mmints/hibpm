#pragma once

#include <vector>

#include "Automaton/Automaton.hpp"
#include "Declare/Declare.hpp"

namespace hibpm
{
    /**
     * Abstract Super Class that is divided further into Unary (Unary.hpp/ -.cpp) and Binary (Binary.hpp/ -.cpp).
     * This Classes are logical containers of DECLARE rules, including all data from the parsed file with an additional
     * Automaton that represents the appropriated rule.
     */
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

        virtual void initializeAutomaton() = 0;
    };
}

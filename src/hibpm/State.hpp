#pragma once

#include <vector>

#include "Automaton.hpp"
#include "Declare.hpp"

namespace hibpm
{
    /**
     * Abstract Super Class that is divided further into Unary (Unary.hpp/ -.cpp) and Binary (Binary.hpp/ -.cpp).
     * This Classes are logical containers of DECLARE rules, including all data from the parsed file with an additional
     * Automaton that represents the appropriated rule.
     *
     * This is the main class behind the logic of the Declare Object.
     * Use this Class for all further calculations.
     * Be aware that their are two further Classes Unary and Binary that extends State due to specific functionality
     * depending on their Type.
     * Each RuleType therefore has a separated extension of Unary or Binary.
     */
    class State
    {
    public:
        /**
         * Constructor of the State Class.
         * Be aware that the main implementation is done in the extensions Unary and Binary.
         * @param rule
         * @param sigmaSize
         * @param is_binary
         */
        State(Rule &rule, size_t sigmaSize, bool is_binary);
        virtual ~State() = default;

        /**
         * Hand over the Rule Struct that holds the RuleType and a Vector of Events
         * @return Rule Struct Object
         */
        Rule getRule();

        /**
         * Get the RuleType from the Rule Struct and returns it.
         * @return RuleType of the current State
         */
        RuleType getRuleType();

        /**
         * Returns the equivalent Automaton for the RuleType of the State.
         * The Automaton is created by the Constructor.
         * @return Automaton Object equivalent to the RuleType of the State
         */
        Automaton getAutomata();

        /**
         * Is True, if the State is Binary.
         * @return bool
         */
        bool isBinary();

        /**
         * Is True, if the State is Unary.
         * @return bool
         */
        bool isUnary();

    protected:
        Rule m_rule;
        size_t m_sigmaSize;
        Automaton m_automaton;
        bool m_is_binary;

        virtual void initializeAutomaton() = 0;
    };
}

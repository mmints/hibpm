#include "State.hpp"

namespace hibpm
{
    State::State(Rule &rule, size_t sigmaSize, bool is_binary) :
        m_rule(rule),
        m_sigmaSize(sigmaSize),
        m_is_binary(is_binary)
    {}

    Rule State::getRule() {
        return m_rule;
    }

    RuleType State::getRuleType() {
        return m_rule.getRuleType();
    }

    Automaton State::getAutomata() {
        return m_automaton;
    }

    bool State::isBinary() {
        return m_is_binary;
    }

    bool State::isUnary() {
        return !m_is_binary; // Just negate the binary variable
    }
}
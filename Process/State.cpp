#include "State.hpp"

namespace hibpm
{
        State::State(Rule &rule, size_t sigmaSize) :
            m_rule(rule),
            m_sigmaSize(sigmaSize)
        {}

        Rule State::getRule() {
            return m_rule;
        }

        RuleType State::getRuleType() {
            return m_rule.type;
        }

        Automaton State::getAutomata() {
            return m_automaton;
        }
}
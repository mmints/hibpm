#include "Rule.hpp"

namespace hibpm
{
    Rule::Rule(size_t sigmaSize, bool isBinary) :
        m_sigmaSize(sigmaSize),
        m_isBinary(isBinary)
    {}

    bool Rule::isBinary() {
        return m_isBinary;
    }

    bool Rule::isUnary() {
        return !m_isBinary;
    }

    Automaton Rule::getAutomata() {
        return m_automaton;
    }

    RuleType Rule::getType() {
        return m_type;
    }

    std::string Rule::getTypeString() {
        return m_ruleTypeString;
    }
}
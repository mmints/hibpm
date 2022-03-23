#include "Constraint.hpp"

namespace hibpm
{
    Constraint::Constraint(size_t sigmaSize, bool isBinary) :
        m_sigmaSize(sigmaSize),
        m_isBinary(isBinary)
    {}

    bool Constraint::isBinary() {
        return m_isBinary;
    }

    bool Constraint::isUnary() {
        return !m_isBinary;
    }

    Automaton Constraint::getAutomata() {
        return m_automaton;
    }

    ConstraintType Constraint::getType() {
        return m_type;
    }

    std::string Constraint::getTypeString() {
        return m_constraintTypeString;
    }
}
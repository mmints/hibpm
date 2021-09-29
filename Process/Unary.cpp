#include "Unary.hpp"

namespace hibpm
{
    Unary::Unary(Rule &rule, size_t sigmaSize) :
    State(rule, sigmaSize),
    m_event(rule.events[0])
    {}

    Event Unary::getEvent() {
        return m_event;
    }

    u_int64_t Unary::getEventNumericValue() {
        return m_event.numericValue;
    }

    // Implementation of Unary Process Types

    // Constructors
    Participation::Participation(Rule &rule, size_t sigmaSize) : Unary(rule, sigmaSize) {
        Participation::initializeAutomaton();
    }

    AtMostOne::AtMostOne(Rule &rule, size_t sigmaSize) : Unary(rule, sigmaSize) {
        AtMostOne::initializeAutomaton();
    }

    Init::Init(Rule &rule, size_t sigmaSize) : Unary(rule, sigmaSize) {
        Init::initializeAutomaton();
    }

    End::End(Rule &rule, size_t sigmaSize) : Unary(rule, sigmaSize) {
        End::initializeAutomaton();
    }

    // Automata Implementations
    void Participation::initializeAutomaton() {
        // TODO: Impl
    }

    void AtMostOne::initializeAutomaton() {
        // TODO: Impl
    }

    void Init::initializeAutomaton() {
        // TODO: Impl
    }

    void End::initializeAutomaton() {
        // TODO: Impl
    }
}
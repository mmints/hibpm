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

    Init::Init(Rule &rule, size_t sigmaSize) : Unary(rule, sigmaSize) {
        Init::initializeAutomaton();
    }

    void Init::initializeAutomaton() {
        // TODO: Impl
    }

    End::End(Rule &rule, size_t sigmaSize) : Unary(rule, sigmaSize) {
        End::initializeAutomaton();
    }

    void End::initializeAutomaton() {
        // TODO: Impl
    }
}
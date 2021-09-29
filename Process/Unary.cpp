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

    Participation::Participation(Rule &rule, size_t sigmaSize) : Unary(rule, sigmaSize) {
        Participation::initializeAutomaton();
    }

    void Participation::initializeAutomaton() {
        // TODO: Impl
    }

    AtMostOne::AtMostOne(Rule &rule, size_t sigmaSize) : Unary(rule, sigmaSize) {
        AtMostOne::initializeAutomaton();
    }

    void AtMostOne::initializeAutomaton() {
        // TODO: Impl
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
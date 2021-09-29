#include "Binary.hpp"

namespace hibpm
{
    Binary::Binary(Rule &rule, size_t sigmaSize) :
        State(rule, sigmaSize),
        m_event_1(rule.events[0]),
        m_event_2(rule.events[1])
    {}

    std::vector<Event> Binary::getEvents() {
        return {m_event_1, m_event_2};
    }

    std::vector<u_int64_t> Binary::getEventNumericValues() {
        return {m_event_1.numericValue, m_event_2.numericValue};
    }

    // Constructors
    RespondedExistence::RespondedExistence(Rule &rule, size_t sigmaSize) : Binary(rule, sigmaSize) {
        RespondedExistence::initializeAutomaton();
    }

    Response::Response(Rule &rule, size_t sigmaSize) : Binary(rule, sigmaSize) {
        Response::initializeAutomaton();
    }

    AlternatedResponse::AlternatedResponse(Rule &rule, size_t sigmaSize) : Binary(rule, sigmaSize) {
        AlternatedResponse::initializeAutomaton();
    }

    ChainResponse::ChainResponse(Rule &rule, size_t sigmaSize) : Binary(rule, sigmaSize) {
        ChainResponse::initializeAutomaton();
    }

    Precedence::Precedence(Rule &rule, size_t sigmaSize) : Binary(rule, sigmaSize) {
        Precedence::initializeAutomaton();
    }

    AlternatedPrecedence::AlternatedPrecedence(Rule &rule, size_t sigmaSize) : Binary(rule, sigmaSize) {
        AlternatedPrecedence::initializeAutomaton();
    }

    ChainPrecedence::ChainPrecedence(Rule &rule, size_t sigmaSize) : Binary(rule, sigmaSize) {
        ChainPrecedence::initializeAutomaton();
    }

    CoExistence::CoExistence(Rule &rule, size_t sigmaSize) : Binary(rule, sigmaSize) {
        CoExistence::initializeAutomaton();
    }

    Succession::Succession(Rule &rule, size_t sigmaSize) : Binary(rule, sigmaSize) {
        Succession::initializeAutomaton();
    }

    AlternateSuccession::AlternateSuccession(Rule &rule, size_t sigmaSize) : Binary(rule, sigmaSize) {
        AlternateSuccession::initializeAutomaton();
    }

    ChainSuccession::ChainSuccession(Rule &rule, size_t sigmaSize) : Binary(rule, sigmaSize) {
        ChainSuccession::initializeAutomaton();
    }

    NotChainSuccession::NotChainSuccession(Rule &rule, size_t sigmaSize) : Binary(rule, sigmaSize) {
        NotChainSuccession::initializeAutomaton();
    }

    NotSuccession::NotSuccession(Rule &rule, size_t sigmaSize) : Binary(rule, sigmaSize) {
        NotSuccession::initializeAutomaton();
    }

    NotCoExistence::NotCoExistence(Rule &rule, size_t sigmaSize) : Binary(rule, sigmaSize) {
        NotCoExistence::initializeAutomaton();
    }
}

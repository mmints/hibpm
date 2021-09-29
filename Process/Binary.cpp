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

// ------
    RespondedExistence::RespondedExistence(Rule &rule, size_t sigmaSize) : Binary(rule, sigmaSize) {
        RespondedExistence::initializeAutomaton();
    }

    void RespondedExistence::initializeAutomaton() {
        // TODO: Impl
    }
// ------

// ------
    Response::Response(Rule &rule, size_t sigmaSize) : Binary(rule, sigmaSize) {
        Response::initializeAutomaton();
    }

    void Response::initializeAutomaton() {
        // TODO: Impl
    }
// ------

// ------
    AlternatedResponse::AlternatedResponse(Rule &rule, size_t sigmaSize) : Binary(rule, sigmaSize) {
        AlternatedResponse::initializeAutomaton();
    }

    void AlternatedResponse::initializeAutomaton() {
        // TODO: Impl
    }
// ------

// ------
    ChainResponse::ChainResponse(Rule &rule, size_t sigmaSize) : Binary(rule, sigmaSize) {
        ChainResponse::initializeAutomaton();
    }

    void ChainResponse::initializeAutomaton() {
        // TODO: Impl
    }
// ------

// ------
    Precedence::Precedence(Rule &rule, size_t sigmaSize) : Binary(rule, sigmaSize) {
        Precedence::initializeAutomaton();
    }

    void Precedence::initializeAutomaton() {
        // TODO: Impl
    }
// ------

// ------
    AlternatedPrecedence::AlternatedPrecedence(Rule &rule, size_t sigmaSize) : Binary(rule, sigmaSize) {
        AlternatedPrecedence::initializeAutomaton();
    }

    void AlternatedPrecedence::initializeAutomaton() {
        // TODO: Impl
    }
// ------

// ------
    ChainPrecedence::ChainPrecedence(Rule &rule, size_t sigmaSize) : Binary(rule, sigmaSize) {
        ChainPrecedence::initializeAutomaton();
    }

    void ChainPrecedence::initializeAutomaton() {
        // TODO: Impl
    }
// ------

// ------
    CoExistence::CoExistence(Rule &rule, size_t sigmaSize) : Binary(rule, sigmaSize) {
        CoExistence::initializeAutomaton();
    }

    void CoExistence::initializeAutomaton() {
        // TODO: Impl
    }
// ------

// ------
    Succession::Succession(Rule &rule, size_t sigmaSize) : Binary(rule, sigmaSize) {
        Succession::initializeAutomaton();
    }

    void Succession::initializeAutomaton() {
        // TODO: Impl
    }
// ------

// ------
    AlternateSuccession::AlternateSuccession(Rule &rule, size_t sigmaSize) : Binary(rule, sigmaSize) {
        AlternateSuccession::initializeAutomaton();
    }

    void AlternateSuccession::initializeAutomaton() {
        // TODO: Impl
    }
// ------

// ------
    ChainSuccession::ChainSuccession(Rule &rule, size_t sigmaSize) : Binary(rule, sigmaSize) {
        ChainSuccession::initializeAutomaton();
    }

    void ChainSuccession::initializeAutomaton() {
        // TODO: Impl
    }
// ------

// ------
    NotChainSuccession::NotChainSuccession(Rule &rule, size_t sigmaSize) : Binary(rule, sigmaSize) {
        NotChainSuccession::initializeAutomaton();
    }

    void NotChainSuccession::initializeAutomaton() {
        // TODO: Impl
    }
// ------

// ------
    NotSuccession::NotSuccession(Rule &rule, size_t sigmaSize) : Binary(rule, sigmaSize) {
        NotSuccession::initializeAutomaton();
    }

    void NotSuccession::initializeAutomaton() {
        // TODO: Impl
    }
// ------

// ------
    NotCoExistence::NotCoExistence(Rule &rule, size_t sigmaSize) : Binary(rule, sigmaSize) {
        NotCoExistence::initializeAutomaton();
    }

    void NotCoExistence::initializeAutomaton() {
        // TODO: Impl
    }
// ------
}

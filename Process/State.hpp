#pragma once

#include "Automaton/Automaton.hpp"
#include "Declare/Declare.hpp"

namespace hibpm
{
    struct State
    {
        RuleType ruleType;
        size_t sigmaS;
        Automaton automaton;

        // Unary
        u_int64_t eventValue;

        // Binary
        u_int64_t eventValue2;
    };

    struct Unary : State{};
    struct Binary : State{};

    struct Participation : Unary {};
    struct AtMostOne : Unary {};
    struct Init : Unary {};
    struct End : Unary {};

    struct RespondedExistence : Binary {};
    struct Response : Binary {};
    struct AlternatedResponse : Binary {};
    struct ChainResponse : Binary {};
    struct Precedence : Binary {};
    struct AlternatedPrecedence : Binary {};
    struct ChainPrecedence : Binary {};
    struct CoExistence : Binary {};
    struct Succession : Binary {};
    struct AlternateSuccession : Binary {};
    struct ChainSuccession : Binary {};
    struct NotChainSuccession : Binary {};
    struct NotSuccession : Binary {};
    struct NotCoExistence : Binary {};
}
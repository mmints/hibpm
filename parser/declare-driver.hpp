#include "Declare/Declare.hpp"
#include "declare-parser.hpp"

hibpm::RuleType tokenToRuleType(yy::declare::token::token_kind_type tk_type)
{
    switch (tk_type)
    {
    case yy::declare::token::PARTICIPATION:
        return hibpm::PARTICIPATION;
        break;
    
    case yy::declare::token::INIT:
        return hibpm::INIT;
    
    default:
        break;
    }
}
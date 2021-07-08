#pragma once

#include<string>
#include<iostream>
#include"Declare/Declare.hpp"
#include"declare-parser.hpp"

// Helping Function: Turns a char* (in this case yytext) into a string and removes all unecessary chars following by the value.
std::string convertCharToString(std::string &delimiter, char *s);

// x occurs at least once
void participation(char* x);

// x occurs at most once
void atMostOne(char* x);

// x is the first to occur
void init(char* x);

// x is the last to occur
void end(char* x);

// whenever x occurs, y occurs
void respondedExistence(char* x, char* y);

// if x occurs, then y occurs after x
void response(char* x, char* y);

// if x occurs then y occurs after it without any other x in between
void alternatedResponse(char* x, char* y);

// if x occurs then y occurs just after it
void chainResponse(char* x, char* y);

// x precedes y
void precedence(char* x, char* y);

// whenever y occurs, x precedes y with no other y in between
void alternatedPrecedence(char* x, char* y);

// whenever y occurs, x precedes y just before it
void chainPrecedence(char* x, char* y);

// x occurs iff y also occurs
void coExistence(char* x, char* y);

// if x occurs then y occurs after it, and if y occurs then x precedes y
void succession(char* x, char* y);

// x and y occurs alternating without any other x and y in between
void alternatedSuccession(char* x, char* y);

// if x occurs then y occurs just after it, and if y occurs then x occurs just before it
void chainSuccession(char* x, char* y);

// y does not occur just after x
void notChainSuccession(char* x, char* y);

// x never occurs before y
void notSuccession(char* x, char* y);

// x and y cannot jointly occur
void notCoExistence(char* x, char* y);

hibpm::RuleType tokenToRuleType(int tk_type)
{
    switch (tk_type)
    {
    case yy::declare::token::PARTICIPATION:
        return hibpm::PARTICIPATION;
        break;
    
    default:
        break;
    }
}
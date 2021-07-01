/* Bison Parser for Decare */

%language "C++" /* Tell Bison that this is C++ */
%require "3.2"  /* Used for modern location error implementation*/
%defines        /* Create Header File */
%locations      /* Handle locations in the parser */

%define api.parser.class {declare} /* The class that will be created gets this name */
/* This class is the context class  */

/* Some initial C++ Code */
%{
#include <iostream>
#include <string>
#include "Declare/Declare.hpp"
#include "location.hh" // This is said by the generated files

// Turns a char* (in this case yytext) into a string and removes all unecessary chars following by the value.
std::string convertCharToString(const std::string &delimiter, char *s)
{
    std::string input(s); // Construct String from Char
    return input.substr(0, input.find(delimiter));
}

%}

/* Use the Declare Data Structure Class as context for the parser. */
%parse-param { hibpm::Declare &daclare_ctx }
%lex-param { hibpm::Declare &daclare_ctx }

/* The value that should be headed over to the main program. */
%union {
    // std::string event_name_val;
    char* event_name_val;
};

/* declare tokens */

/* Unary */
%token PARTICIPATION
%token AT_MOST_ONE
%token INIT
%token END

/* Binary */
%token RESPONDED_EXISTENCE
%token RESPONSE
%token ALTERNATED_RESPONSE
%token CHAIN_RESPONSE
%token PRECEDENCE
%token ALTERNATED_PRECEDENCE
%token CHAIN_PRECEDENCE
%token CO_EXISTENCE
%token SUCCESSION
%token ALTERNATED_SUCCESSION
%token CHAIN_SUCCESSION
%token NOT_CHAIN_SUCCESSION
%token NOT_SUCCESSION
%token NOT_CO_EXISTENCE

/* General Chars used in DECLARE definitions */
%token OP CL QUOTE COMMA EOL

%token <event_name_val> VAR

/* For some reason, bison doesn’t create the declaration of yylex that C++ requires, so we do it manually here. */
%{
extern int yylex(yy::declare::semantic_type *yylval, // Custom yylex declaration
        yy::declare::location_type* yylloc,
        hibpm::Declare &daclare_ctx);
%}

%initial-action {
// Filename for locations here
@$.begin.filename = @$.end.filename = new std::string("stdin");
}

%%

exp: exp exp
 | rule
 ;

rule: PARTICIPATION OP QUOTE VAR QUOTE CL EOL { std::string val = convertCharToString("'", $4);
                                                daclare_ctx.addRule(hibpm::PARTICIPATION, val);
                                              }
;

rule: RESPONDED_EXISTENCE OP QUOTE VAR QUOTE COMMA QUOTE VAR QUOTE CL EOL { std::string val_1 = convertCharToString("'",$4);
                                                                            std::string val_2 = convertCharToString("'",$8);
                                                                            hibpm::Event event_1 {val_1};
                                                                            hibpm::Event event_2 {val_2};
                                                                            hibpm::Rule rule {hibpm::RESPONDED_EXISTENCE, std::vector<hibpm::Event>{event_1, event_2}};
                                                                            daclare_ctx.addRule(rule);
                                                                          }
;

%%

// Main code in separated main.cpp file
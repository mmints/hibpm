/* Bison Parser for Decare */

%language "C++" /* Tell Bison that this is C++ */
%defines        /* Create Header File */
%locations      /* Handle locations in the parser */

%define api.parser.class {declare} /* The class that will be created gets this name */
/* This class is the context class  */

/* Some initial C++ Code */
%{
#include <iostream>
#include <string>
#include "Declare/Declare.hh"
%}

%parse-param { hibpm::Declare &ctx }
%lex-param { hibpm::Declare &ctx }

%union {
    std::string event_name_val;
};

/* declare tokens */

/* Unary */
%token PARTICIPATION

/* Binary */
%token RESPONDED_EXISTENCE

/* General Chars used in DECLARE definitions */
%token OP CL QUOTE COMMA EOL

%token <event_name_val> VAR

/* For some reason, bison doesn’t create the declaration of yylex that C++ requires, so we do it manually here. */
%{
extern int yylex(yy::declare::semantic_type *yylval, // Custom yylex declaration
        yy::declare::location_type* yylloc,
        hibpm::Declare &ctx);
%}

%initial-action {
// Filename for locations here
@$.begin.filename = @$.end.filename = new std::string("stdin");
}

%%

exp: exp exp
 | rule
 ;

rule: PARTICIPATION OP QUOTE VAR QUOTE CL EOL { std::cout << "Rule: PARTICIPATION " << "Event: " << $4 << std::endl; }
;

rule: RESPONDED_EXISTENCE OP QUOTE VAR QUOTE COMMA QUOTE VAR QUOTE CL EOL { std::cout << "Rule: RESPONDED_EXISTENCE " << "Events: " << $4 << " and " << $8 << std::endl; }
;

%%

namespace yy
{
    void declare::error(location const &loc, const std::string& s) {
        std::cerr << "error at " << loc << ": " << s << std::endl;
    }
}
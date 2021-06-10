/* Include the Bison Parser Header for Tokens */
%{
# include <string.h>
# include "parser.h"
%}

%option noyywrap

%%

"Participation"         { return PARTICIPATION; }
"AtMostOne"             { return AT_MOST_ONE; }
"Init"                  { return INIT; }
"End"                   { return END; }
"RespondedExistence"    { return RESPONDED_EXISTENCE; }
"Response"              { return RESPONSE; }
"AlternatedResponse"    { return ALTERNATED_RESPONSE; }
"ChainResponse"         { return CHAIN_RESPONSE; }
"Precedence"            { return PRECEDENCE; }
"AlternatedPrecedence"  { return ALTERNATED_PRECEDENCE; }
"ChainPrecedence"       { return CHAIN_PRECEDENCE; }
"CoExistence"           { return CO_EXISTENCE; }
"Succession"            { return SUCCESSION; }
"AlternatedSuccession"  { return ALTERNATED_SUCCESSION; }
"ChainSuccession"       { return CHAIN_SUCCESSION; }
"NotChainSuccession"    { return NOT_CHAIN_SUCCESSION; }
"NotSuccession"         { return NOT_SUCCESSION; }
"NotCoExistence"        { return NOT_CO_EXISTENCE; }

"("    { return OP; }
")"    { return CL; }
"'"    { return QUOTE; }
","    { return COMMA; }

([a-zA-Z0-9]+(?:_?[a-zA-Z0-9]+)*) { yylval.text = yytext;
                                    return VAR; }

\n     { return EOL; }
[ \t]  { }
.      { printf("Mystery character %s\n", yytext); }

%%

/*

"\""   { return QUOTE; }
Participation('O_CreateOffer')

*/
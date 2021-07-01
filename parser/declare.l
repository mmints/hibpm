/* Include the Bison Parser Header for Tokens */

%option noyywrap

%{
#include "Declare/Declare.hh"
#include "declare.tab.hh"

// defines YY_DECL to declare the calling sequence for yylex to match what the parser expects
#define YY_DECL int yylex(yy::declare::semantic_type *yylval, yy::declare::location_type *yylloc, hibpm::Declare &ctx)

// make location include the current token
// defines YY_USER_ACTION, the macro invoked before the action for each token, to set the location based on the length of the token
# define YY_USER_ACTION yylloc->columns (yyleng);
typedef yy::declare::token token;
%}

%%

%{
// start where previous token ended
yylloc->step ();
%}

"Participation"         { return token::PARTICIPATION; }

"RespondedExistence"    { return token::RESPONDED_EXISTENCE; }

"("    { return token::OP; }
")"    { return token::CL; }
"'"    { return token::QUOTE; }
"\""    { return token::D_QUOTE; }
","    { return token::COMMA; }

([a-zA-Z0-9]+(?:_?[a-zA-Z0-9]+)*) { yylval->event_name_val = yytext; return token::VAR; }

\n     { return token::EOL; }
[ \t]  { yylloc->step (); }
.      { printf("Mystery character %s\n", yytext); }

%%

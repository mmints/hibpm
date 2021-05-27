%{
// # include "declare_rules"
#include <stdio.h>
#include <string.h>
int yylex();
int yyerror();
%}

%union {
  char* text;
}

/* declare tokens */
%token PARTICIPATION
%token AT_MOST_ONE
%token INIT
%token END
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

%token OP CL QUOTE COMMA EOL

%token <text> VAR

%%

exp: exp exp
 | rule                      
 ;

rule: PARTICIPATION OP QUOTE VAR QUOTE CL EOL { printf("VAR: %s", $4); }
;

%%

yyerror(char *s)
{
  fprintf(stderr, "error: %s \n", s);
}
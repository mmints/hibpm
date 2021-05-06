/* This is a simple Scanner File that prints out the tokens that are read in. */

%option noyywrap

%%

"Participation"    { printf("Participation\n"); }

"AtMostOne"    { printf("AtMostOne\n"); }

"Init"    { printf("Init\n"); }

"End"    { printf("End\n"); }

"RespondedExistence"    { printf("RespondedExistence\n"); }

"Response"    { printf("Response\n"); }

"AlternatedResponse"    { printf("AlternatedResponse\n"); }

"ChainResponse"    { printf("ChainResponse\n"); }

"Precedence"    { printf("Precedence\n"); }

"AlternatedPrecedence"    { printf("AlternatedPrecedence\n"); }

"ChainPrecedence"    { printf("ChainPrecedence\n"); }

"CoExistence"    { printf("CoExistence\n"); }

"Succession"    { printf("Succession\n"); }

"AlternatedSuccession"    { printf("AlternatedSuccession\n"); }

"ChainSuccession"    { printf("ChainSuccession\n"); }

"NotChainSuccession"    { printf("NotChainSuccession\n"); }

"NotSuccession"    { printf("NotSuccession\n"); }

"NotCoExistence"    { printf("NotCoExistence\n"); }

"("    { printf("OP\n"); }
")"    { printf("CL\n"); }
"'"    { printf("QUOTE \n"); }
"\""    { printf("QUOTE \n"); }
","    { printf("COMMA\n"); }

([a-zA-Z0-9]+(?:_?[a-zA-Z0-9]+)*) { printf("VAR %s\n", yytext); }

\n     { printf("NEWLINE\n"); }
[ \t]  { }
.      { printf("Mystery character %s\n", yytext); }

%%

/* Maybe some execution code, but not needed.*/

int main(int argc, char **argv)
{
  yylex();
}
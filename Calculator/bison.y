%{
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern int yyparse();
extern FILE *yyin;
	
void yyerror(char *s);
	 
%}

%union {
	float fval;
	char *sval;
}
%token <fval> NUM
%token <sval> IDENTIFIER
%type <fval> exp
%type <sval> declaration
%left '-' '+'
%left '*' '/'
%left NEG /*menos unario*/
%right '^'

%%
input:	/*vacío*/
		| input line
;

line:	'\n'			{printf(">");}
		| exp '\n' 		{printf("\t%f\n>", $1);}
;

exp:	NUM				{$$ = $1;}
		| exp '+' exp	{$$ = $1 + $3;}
		| exp '-' exp	{$$ = $1 - $3;}
		| exp '*' exp	{$$ = $1 * $3;}
		| exp '/' exp	{$$ = $1 / $3;}
		| '-' exp		{$$ = -$2;}
		| exp '^' exp	{$$ = pow ($1, $3);}
		| '(' exp ')'	{$$ = $2;}
;

declaration: IDENTIFIER '=' NUM {$$ = $3;}
;
%%

int main() {
	yyparse();
	
	return(EXIT_SUCCESS);
}

 void yyerror (char *s) {
   fprintf (stderr, "%s\n", s);
 }

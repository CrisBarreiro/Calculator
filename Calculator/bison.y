%{
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "Tsim.h"

extern int yylex();
extern int yyparse();
extern FILE *yyin;
	
void yyerror(const char *s);
	 
%}

%define parse.error verbose

%union {
	double fval;
	entrada eval;
}
%token <fval> NUM
%token <eval> IDENTIFIER
%token <eval> CONSTANT
%token <eval> FUNCTION
%left '='
%left '-' '+'
%left '*' '/'
%left NEG /*menos unario*/
%right '^'
%type <fval> exp

%%
input:	/*vacío*/
		| input line
;

line:	'\n'					{printf(">");}
		| exp '\n' 				{printf("\t%f\n>", $1);}
		| error '\n'				{yyerrok; printf(">");}  
;

exp:	NUM						{$$ = $1;}
		| IDENTIFIER			{$$=$1.valor.var;}
		| CONSTANT 				{$$=$1.valor.var;}
		| IDENTIFIER '=' exp	{
									entrada e = NUEVA_ENTRADA($1.lexema, VAR, $3);
									$$ = $3;
									
								}
		| '(' exp ')'			{$$ = $2;}
		| exp '+' exp			{$$ = $1 + $3;}
		| exp '-' exp			{$$ = $1 - $3;}
		| exp '*' exp			{$$ = $1 * $3;}
		| exp '/' exp			{$$ = $1 / $3;}
		| '-' exp %prec NEG		{$$ = -$2;}
		| exp '^' exp			{$$ = pow ($1, $3);}
		
;

%%

int main() {
    CREAR_TABLA();
	yyparse();
	
	return(EXIT_SUCCESS);
}

 void yyerror (const char *s) {
   fprintf (stderr, "%s\n", s);
 }

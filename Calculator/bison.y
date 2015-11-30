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
		| exp '\n' 				{
									/*Una línea que no termine en ';', se imprime*/
									printf("\t%f\n>", $1);}
		| exp ';' '\n'			{
									/*Una línea seguida terminada en ';' implica que el resultado no se imprima*/
									printf("\n>");
		
								}
		| error '\n'			{yyerrok; printf(">");}  
;

exp:	NUM						{$$ = $1;}
		| IDENTIFIER			{$$=$1.valor.var;}
		| CONSTANT 				{$$=$1.valor.var;}
		| IDENTIFIER '=' exp	{
									/*Al asignar una variable, se añade a la tabla de símbolos*/
									entrada e;
									e.lexema = $1.lexema;
									e.tipo = VAR;
									e.valor.var = $3;
									NUEVA_ENTRADA(e);
									$$ = $3;
									
								}
		| FUNCTION '(' exp ')'		{
		
									if (strcmp($1.lexema, "sqrt") == 0 && $3 < 0) {
										yyerror("syntax error, unexpected negative number");
										YYERROR;
									} else {
										$$ = $1.valor.func($3);
									}
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

int main(int argc, char **argv) {
    CREAR_TABLA();
    printf(">");
    if (argc == 2) {
    	FILE *fp = fopen(argv[1], "rt");
    	if (fp == NULL) {
    		fprintf(stderr, "File not found");
    	} else {
    		printf("Loading file %s", argv[1]);
    		yyset_in(fp);
    	}
    	
    } else {
    	printf("Starting program in command-line mode\n");
    }
	yyparse();
	
	return(EXIT_SUCCESS);
}

 void yyerror (const char *s) {
   printf ("ERROR: %s\n", s);
 }

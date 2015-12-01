%{
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "Tsim.h"
#include "help.h"

extern int yylex();
extern int yyparse();
extern FILE *yyin;
	
void yyerror(const char *s);
	 
%}

%define parse.error verbose

/*El lexema procesado puede ser un double o una entrada (definida en Tsim.h)*/
%union {
	double fval;
	entrada eval;
}

/*Símbolos no terminales de la gramática*/
%token <fval> NUM
%token <eval> IDENTIFIER
%token <eval> CONSTANT

/*Comandos especiales*/
%token <fval> EXIT
%token <fval> VARIABLES
%token <fval> CONSTANTS
%token <fval> FUNCTIONS
%token <fval> USERHELP

/*Símbolos terminales de la gramática*/
%token <eval> FUNCTION
/*Definimos la precedencia de operadores (las operaciones con mayor precedencia
* son las que se sitúan más abajo*/
%left '='
%left '-' '+'
%left '*' '/'
%left NEG /*menos unario*/
%right '^'
/*Los lexemas que cumplen la regla 'exo' son de tipo fval, en este caso double*/
%type <fval> exp

%%
input:	/*vacío*/
		| input line
;

/*Una línea viene definida por un salto de línea, una expresión seguida de salto de línea, una expresión
* seguida por un punto y coma y un salto de línea, o un error seguido de un salto de línea*/
line:	'\n'					{printf(">");}
		| exp '\n' 				{
									/*Una línea que no termine en ';', se imprime*/
									printf("\t%f\n>", $1);}
		| exp ';' '\n'			{
									/*Una línea seguida terminada en ';' implica que el resultado no se imprima*/
									printf("\n>");
		
								}
		| error '\n'			{
									/*Se lanza un error y se continúa con la ejecución*/
									yyerrok; printf(">");
								}  
		| EXIT '\n'				{
									exit(0);
								}
		| VARIABLES '\n'		{
									IMPRIMIR_VARIABLES();
									printf("\n>");
								}
		| CONSTANTS '\n'		{
									IMPRIMIR_CONSTANTES();
									printf("\n>");
								}
		| FUNCTIONS '\n'		{
									IMPRIMIR_FUNCIONES();
									printf("\n>");
								}
		| USERHELP '\n'				{
									COMPLETE_HELP();
									printf("\n>");
								}
;

/*Una expresión viene defiida por:*/
		/* - Un número*/
exp:	NUM						{$$ = $1;}
		/* - Un identificador*/
		| IDENTIFIER			{	
									if (!isnan($1.valor.var)) {
										$$=$1.valor.var;
									} else {
										yyerror("syntax error, varible not initialized");
										YYERROR;
									}
									
								}
		/* - Una constante*/
		| CONSTANT 				{$$=$1.valor.var;}
		/* - Un identificador igualado a una expresión*/
		| IDENTIFIER '=' exp	{
									/*Al asignar una variable, se añade a la tabla de símbolos*/
									entrada e;
									e.lexema = $1.lexema;
									e.tipo = VAR;
									e.valor.var = $3;
									NUEVA_ENTRADA(e);
									$$ = $3;
									
								}
		/* - Una llamada a función con una expresión como argumento*/
		| FUNCTION '(' exp ')'		{
									/*Si se intenta hacer la raí cuadrada de un número negativo
									* se lanza un error*/
									if (strcmp($1.lexema, "sqrt") == 0 && $3 < 0) {
										yyerror("syntax error, unexpected negative number");
										YYERROR;
									} else {
										$$ = $1.valor.func($3);
									}
								}
		/* - Una expresión entre paréntesis*/
		| '(' exp ')'			{$$ = $2;}
		/* - Suma, resta, multiplicación y división de 2 expresiones*/
		| exp '+' exp			{$$ = $1 + $3;}
		| exp '-' exp			{$$ = $1 - $3;}
		| exp '*' exp			{$$ = $1 * $3;}
		| exp '/' exp			{$$ = $1 / $3;}
		/* - El puesto de una expresión*/
		| '-' exp %prec NEG		{$$ = -$2;}
		/* - Una expresión elevada a otra expresión*/
		| exp '^' exp			{$$ = pow ($1, $3);}
		
;

%%

int main(int argc, char **argv) {
	/*Se crea la tabla*/
    CREAR_TABLA();
    if (argc == 2) {
    	if (strcmp(argv[1], "-h") == 0) {
    		printf("--------------------Calculadora v0.1--------------------\n");
    		HELP();
    		exit(0);
    	} else if (strcmp(argv[1], "--help") == 0){
    		printf("--------------------Calculadora v0.1--------------------\n");
    		COMPLETE_HELP();
    		exit(0);
    	} else {
    		FILE *fp = fopen(argv[1], "rt");
    		if (fp == NULL) {
    			fprintf(stderr, "File not found");
    		} else {
    			printf("Loading file %s", argv[1]);
    			/*Se establece el archivo indicado por línea de comandos como
    			* entrada del programa*/
    			yyset_in(fp);
    		}
    	}
    
    	
    	
    } else {
    	/*Ejecución del programa en modo interactivo*/
    	printf("Starting program in command-line mode\n");
    	printf("\"help\" command opens user manual\n");
    	printf(">");
    }
	yyparse();
	
	return(EXIT_SUCCESS);
}

 void yyerror (const char *s) {
   printf ("ERROR: %s\n", s);
 }

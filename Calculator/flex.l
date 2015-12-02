%{
/*Biblotecas y variables*/
#include <stdio.h>
#include <stdlib.h>
#include "Tsim.h"
/*Hay que importar la cabecera de bison para poder acceder a sus definiciones*/
#include "bison.tab.h"
#include <math.h>
int linea = 1;
%}
%{
/*Símbolos reconocidos por el programa*/
%}
SYM		"("|")"|";"|","|"="|"+"|">"|"<"|"-"|"*"|"/"|"^"|"."|"{"|"}"|":"|"["|"]"
DIGITO	[[:digit:]]
%{
/*Números en notación científica*/
%}
EXP		e-?{DIGITO}+
ALPHA	[[:alpha:]]
%{
/*Secuencia alfanumérica que empieza por letra o '_'*/
%}
ID		[_[:alpha:]][_[:alnum:]]*

%%
%{
/*En caso de leer un símbolo, se devuelve su codificación ascii*/
%}
{SYM} 	return yytext[0]; 

%{
/*Bloque de reconocimiento de números*/
%}
{DIGITO}+{EXP}	{
					yylval.fval=atof(yytext);
					return NUM;
				}
				
{DIGITO}*		{
					yylval.fval=atof(yytext);
					return NUM;
				}
				
{DIGITO}*"."{DIGITO}+{EXP}?	{
					yylval.fval=atof(yytext);
					return NUM;
				}
				
{DIGITO}+"."{DIGITO}*{EXP}?	{
					yylval.fval=atof(yytext);
					return NUM;
				}
%{
/*Fin del bloque de reconocimiento de números*/
%}
				
{ID} 			{
					/*exit finaliza el programa*/
					if (strcmp(strdup(yytext), "exit") == 0) {
						return EXIT;
					} 
					/*Comandos de impresión del contenido de la tabla de símbolos*/
					else if (strcmp(strdup(yytext), "variables") == 0) {
						return VARIABLES;
					} else if (strcmp(strdup(yytext), "functions") == 0) {
						return FUNCTIONS;
					} else if (strcmp(strdup(yytext), "constants") == 0) {
						return CONSTANTS;
					} 
					/*help abre la ayuda*/
					else if (strcmp(strdup(yytext), "help") == 0) {
						return USERHELP;
					} else {
						/*Se busca el lexema en la tabla de símbolos*/
						entrada e = BUSCAR(yytext);
						yylval.eval.lexema=strdup(yytext);
						yylval.eval.tipo = e.tipo;
						yylval.eval.valor = e.valor;
						if (e.tipo == FUNC) {
							/*Se devuelve un lexema de tipo función*/
							return FUNCTION;
						} else if (e.tipo == CONS) {
							/*Se devuelve un lexema de tipo constante*/
							return CONSTANT;
						} else {
							/*Se devuelve un lexema de tipo identificador*/
							yylval.eval.tipo=IDENTIFIER;
							return IDENTIFIER;
						}
					}
					
					
				}	
\n	return '\n';

<<EOF>>	return EOF;

%%

int yywrap() {
	yyset_in(stdin);
	return 0;
}

%option noyywrap
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

SYM		"("|")"|";"|","|"="|"+"|">"|"<"|"-"|"*"|"/"|"^"|"."|"{"|"}"|":"|"["|"]"
DIGITO	[[:digit:]]
EXP		e-?{DIGITO}+
ALPHA	[[:alpha:]]
ID		[_[:alpha:]][_[:alnum:]]*

%%
{SYM} 	return yytext[0]; 

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
				
{ID} 			{
					if (strcmp(strdup(yytext), "exit") != 0) {
						entrada e = BUSCAR(yytext);
						yylval.eval.lexema=strdup(yytext);
						yylval.eval.tipo = e.tipo;
						yylval.eval.valor = e.valor;
						if (e.tipo == FUNC) {
							return FUNCTION;
						} else if (e.tipo == CONS) {
							return CONSTANT;
						} else {
							yylval.eval.tipo=IDENTIFIER;
							return IDENTIFIER;
						}
					} else {
						return EXIT;
					}
					
					
				}
				
\n	return '\n';

<<EOF>>	return EOF;

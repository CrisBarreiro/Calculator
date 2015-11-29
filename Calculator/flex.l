%option noyywrap

%{
/*Biblotecas y variables*/
#include <stdio.h>
#include <stdlib.h>
#include "Tsim.h"
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

{SYM} 	return yytext[0]; //s
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
					entrada e = BUSCAR(yytext);
					yylval.eval.lexema=strdup(yytext);
					yylval.eval.tipo = e.tipo;
					yylval.eval.valor = e.valor;
					return IDENTIFIER;
				}
				
\n	return yytext[0];

<<EOF>>	return EOF;

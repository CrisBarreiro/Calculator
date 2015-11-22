%option noyywrap

%{
/*Biblotecas y variables*/
#include <stdio.h>
#include <stdlib.h>
#include "bison.tab.h"
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
{DIGITO}*	{
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
{ID} return IDENTIFIER;
\n	return yytext[0];
<<EOF>>	return EOF;

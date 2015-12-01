/*Fichero de definición de la tabla de símbolos*/

#include "Tsim.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bison.tab.h"
#include "uthash.h"

/*Estructura que define cada entrada de la tabla*/
typedef struct {
	char* lexema;
	int tipo;
	valorUnion valor;
	UT_hash_handle hh;
} entry;

/*Tabla de símbolos*/
entry *tabla = NULL;

/*Función que busca una entrada en la tabla utilizando el lexema como
 campo de búsqueda*/
entry * BUSCAR_ENTRADA(char *lex) {
	entry *s;
	HASH_FIND_STR(tabla, lex, s);
	return s;
}

entrada BUSCAR(char *lex) {
	entry *s = NULL;
	s = BUSCAR_ENTRADA(lex);
	entrada e;
	if (s != NULL) {
		e.lexema = strdup(s->lexema);
		e.tipo = s->tipo;
		e.valor.var = s->valor.var;
	} else {
		/*Si el lexema no se encuentra ya en la tabla de símboos
		 * sólo puede ser un identificador*/
		e.lexema = lex;
		e.tipo = IDENTIFIER;
		e.valor.var = NAN;
	}
	return e;

}
/*Función privada de manejo de la tabla que añade un componente a la misma*/
void ANHADIR(entrada e) {
	entry *s = NULL;
	s = (entry*) malloc(sizeof(entry));
	s->lexema = strdup(e.lexema);
	s->tipo = e.tipo;
	if (e.tipo == VAR || e.tipo == CONS) {
		s->valor.var = e.valor.var;
	} else if (e.tipo == FUNC) {
		s->valor.func = e.valor.func;
	}

	HASH_ADD_KEYPTR(hh, tabla, s->lexema, strlen(s->lexema), s);
}

/*Función que añade una nueva entrada a la tabla*/
entrada NUEVA_ENTRADA(entrada e) {
	/*Antes de realizar la inserción, se busca en la tabla para saber si
	 el lexema a insertar ya forma parte de la tabla*/
	entry *s = BUSCAR_ENTRADA(e.lexema);
	if (s == NULL) {
		ANHADIR(e);
		return e;
	} else {
		if (s->tipo == CONS || s->tipo == FUNC) {
			e.valor = s->valor;
			e.tipo = s->tipo;
			return e;
		} else {
			HASH_DEL(tabla, s);
			ANHADIR(e);
			e.valor = s->valor;
			e.tipo = s->tipo;
			return e;
		}
	}
}

/*Función que imprime el contenido de la tabla de símbolos*/
void IMPRIMIR_VARIABLES() {
	entry *s, *tmp;
	int i = 0;
	printf("--------------------VARIABLES--------------------\n");
	printf("%-8s\t%-20s%-20s\n", "Indice", "Lexema", "Valor");
	printf("-------------------------------------------------\n");

	HASH_ITER(hh, tabla, s, tmp)
	{
		if (s->tipo == VAR) {
			printf("\n%10d\t%-20s%-20f", i, s->lexema, s->valor.var);
					i++;
		}
	}
}

void IMPRIMIR_CONSTANTES() {
	entry *s, *tmp;
	int i = 0;
	printf("--------------------CONSTANTS--------------------\n");
	printf("%-8s\t%-20s%-20s\n", "Indice", "Lexema", "Valor");
	printf("-------------------------------------------------\n");

	HASH_ITER(hh, tabla, s, tmp)
	{
		if (s->tipo == CONS) {
			printf("\n%10d\t%-20s%-20f", i, s->lexema, s->valor.var);
					i++;
		}
	}
}

void IMPRIMIR_FUNCIONES() {
	entry *s, *tmp;
		int i = 0;
		printf("--------------------CONSTANTS--------------------\n");
		printf("%-8s\t%-20s\n", "Indice", "Lexema");
		printf("-------------------------------------------------\n");

		HASH_ITER(hh, tabla, s, tmp)
		{
			if (s->tipo == FUNC) {
				printf("\n%10d\t%-20s", i, s->lexema);
						i++;
			}
		}
}

void CREAR_ESTRUCTURA_VAR(char *lexema, int tipo, double valor) {
	entrada e;
	e.lexema = strdup(lexema);
	e.tipo = tipo;
	e.valor.var = valor;
	ANHADIR(e);
}

void CREAR_ESTRUCTURA_FUNC(char *lexema, double (*func)()) {
	entrada e;
	e.lexema = strdup(lexema);
	e.tipo = FUNC;
	e.valor.func = func;
	ANHADIR(e);
}

/*Función que inicializa la tabla de símbolos con las palabras reservadas del
 lenguaje*/
void CREAR_TABLA() {

	CREAR_ESTRUCTURA_VAR("pi", CONS, M_PI);

	CREAR_ESTRUCTURA_VAR("e", CONS, M_E);

	CREAR_ESTRUCTURA_FUNC("sqrt", sqrt);

	CREAR_ESTRUCTURA_FUNC("sin", sin);

	CREAR_ESTRUCTURA_FUNC("cos", cos);

	CREAR_ESTRUCTURA_FUNC("tan", tan);

	CREAR_ESTRUCTURA_FUNC("asin", asin);

	CREAR_ESTRUCTURA_FUNC("acos", acos);

	CREAR_ESTRUCTURA_FUNC("atan", atan);

	CREAR_ESTRUCTURA_FUNC("sinh", sinh);

	CREAR_ESTRUCTURA_FUNC("cosh", cosh);

	CREAR_ESTRUCTURA_FUNC("tanh", tanh);

	CREAR_ESTRUCTURA_FUNC("ceil", ceil);

	CREAR_ESTRUCTURA_FUNC("fabs", fabs);

	CREAR_ESTRUCTURA_FUNC("floor", floor);

	CREAR_ESTRUCTURA_FUNC("log", log);

	CREAR_ESTRUCTURA_FUNC("log10", log10);

	CREAR_ESTRUCTURA_FUNC("exp", exp);
}

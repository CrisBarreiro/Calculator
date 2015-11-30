/*Fichero de definición de la tabla de símbolos*/

#include "Tsim.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	} else
		e.valor.var = NAN;
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
void IMPRIMIR() {
	entry *s, *tmp;
	int i = 0;
	printf("--------------------Tabla de símbolos--------------------\n");
	printf("%-8s\t%-20s%-20s\n", "Indice", "Lexema", "Valor");
	printf("---------------------------------------------------------\n");

	HASH_ITER(hh, tabla, s, tmp)
	{
		printf("\n%10d\t%-20s%-20f", i, s->lexema, s->valor.var);
		i++;
	}
}

/*Función que inicializa la tabla de símbolos con las palabras reservadas del
 lenguaje*/
void CREAR_TABLA() {

	entrada e;

	e.lexema = "pi";
	e.tipo = CONS;
	e.valor.var = M_PI;

	ANHADIR(e);

	e.lexema = "e";
	e.tipo = CONS;
	e.valor.var = M_E;

	ANHADIR(e);

	e.lexema = "cos";
	e.tipo = FUNC;
	e.valor.func = cos;

	ANHADIR(e);

	e.lexema = "sqrt";
	e.tipo = FUNC;
	e.valor.func = sqrt;

	ANHADIR(e);

	e.lexema = "sin";
	e.tipo = FUNC;
	e.valor.func = sin;
	ANHADIR(e);

	e.lexema = "tan";
	e.tipo = FUNC;
	e.valor.func = tan;
	ANHADIR(e);

	e.lexema = "atan";
	e.tipo = FUNC;
	e.valor.func = atan;
	ANHADIR(e);

	e.lexema = "log";
	e.tipo = FUNC;
	e.valor.func = log;
	ANHADIR(e);

	e.lexema = "log10";
	e.tipo = FUNC;
	e.valor.func = log10;
	ANHADIR(e);

	e.lexema = "exp";
	e.tipo = FUNC;
	e.valor.func = exp;
	ANHADIR(e);
}

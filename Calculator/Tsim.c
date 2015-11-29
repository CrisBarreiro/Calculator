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
	double valor;
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
		e.valor = s->valor;
	} else
		e.valor = NAN;
	return e;

}
/*Función privada de manejo de la tabla que añade un componente a la misma*/
void ANHADIR(char *lexema, int tipo, double valor) {
	entry *s = NULL;
	s = (entry*) malloc(sizeof(entry));
	s->lexema = strdup(lexema);
	s->tipo = tipo;
	s->valor = valor;
	HASH_ADD_KEYPTR(hh, tabla, s->lexema, strlen(s->lexema), s);
}

/*Función que añade una nueva entrada a la tabla*/
entrada NUEVA_ENTRADA(char *lexema, int tipo, double valor) {
	/*Antes de realizar la inserción, se busca en la tabla para saber si
	 el lexema a insertar ya forma parte de la tabla*/
	entrada e;
	entry *s = BUSCAR_ENTRADA(lexema);
	e.lexema = strdup(lexema);
	if (s == NULL) {
		ANHADIR(lexema, tipo, valor);
		e.valor = valor;
		e.tipo = tipo;
		return e;
	} else {
		if (s->tipo == CONS || s->tipo == FUNC) {
			e.valor = s->valor;
			e.tipo = s->tipo;
			return e;
		} else {
			HASH_DEL(tabla, s);
			ANHADIR(lexema, tipo, valor);
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
		printf("\n%10d\t%-20s%-20f", i, s->lexema, s->valor);
		i++;
	}
}

/*Función que inicializa la tabla de símbolos con las palabras reservadas del
 lenguaje*/
void CREAR_TABLA() {
	ANHADIR("pi", CONS, M_PI);
	ANHADIR("e", CONS, M_E);
}

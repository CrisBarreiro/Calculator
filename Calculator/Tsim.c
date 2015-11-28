/*Fichero de definición de la tabla de símbolos*/

#include <stdio.h>
#include <stdlib.h>
#include "uthash.h"
#include <math.h>

/*Estructura que define cada entrada de la tabla*/
typedef struct {
    char* lexema;
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

/*Función privada de manejo de la tabla que añade un componente a la misma*/
void ANHADIR(char *lexema, double valor) {
    entry *s = NULL;
    s = (entry*) malloc(sizeof (entry));
    s->lexema = (char*) malloc((strlen(lexema) + 1) * sizeof (char));
    strcpy(s->lexema, lexema);
    s->valor = valor;
    HASH_ADD_KEYPTR(hh, tabla, s->lexema, strlen(s->lexema), s);
}

/*Función que añade una nueva entrada a la tabla*/
double NUEVA_ENTRADA(char *lexema, double valor) {
    /*Antes de realizar la inserción, se busca en la tabla para saber si
     el lexema a insertar ya forma parte de la tabla*/
    entry *s = BUSCAR_ENTRADA(lexema);
    if (s == NULL) {
        ANHADIR(lexema, valor);
        return valor;
    } else {
    	HASH_DEL(tabla, s);
    	ANHADIR(lexema, valor);
        return valor;
    }
}

/*Función que imprime el contenido de la tabla de símbolos*/
void IMPRIMIR() {
    entry *s, *tmp;
    int i = 0;
    printf("--------------------Tabla de símbolos--------------------\n");
    printf("%-8s\t%-20s%-20s\n", "Indice", "Lexema", "Tipo");
    printf("---------------------------------------------------------\n");

    HASH_ITER(hh, tabla, s, tmp) {
        printf("\n%10d\t%-20s%-20s", i, s->lexema, s->valor);
        i++;
    }
}

/*Función que inicializa la tabla de símbolos con las palabras reservadas del
 lenguaje*/
void CREAR_TABLA() {
    ANHADIR("pi", M_PI);
    ANHADIR("e", M_E);
}

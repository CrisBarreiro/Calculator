#ifndef TSIM_H_
#define TSIM_H_

#define VAR 0
#define CONS 1
#define FUNC 2

typedef union {
	double var;
	double (*func)();
} valorUnion;

typedef struct {
	char* lexema;
	int tipo;
	valorUnion valor;
} entrada;

/*Inserta una entrada en la tabla de símbolos y
 * devuelve el tipo de componente
 */
entrada NUEVA_ENTRADA(entrada e);

/*Crea la tabla de símbolos con las palabras reservadas del lenguaje*/
void CREAR_TABLA();

/*Imprime el contenido de la tabla de símbolos*/
void IMPRIMIR();

entrada BUSCAR(char *lex);
#endif

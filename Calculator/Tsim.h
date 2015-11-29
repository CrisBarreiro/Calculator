#ifndef TSIM_H_
#define TSIM_H_

#define VAR 0
#define CONS 1
#define FUNC 2

typedef union {
	double var;
	double (*func)();
} union_val;

typedef struct {
	char* lexema;
	int tipo;
	union_val valor;
} entrada;

/*Inserta una entrada en la tabla de símbolos y
 * devuelve el tipo de componente
 */
entrada NUEVA_ENTRADA(char *lexema, int tipo, double valor);

/*Crea la tabla de símbolos con las palabras reservadas del lenguaje*/
void CREAR_TABLA();

/*Imprime el contenido de la tabla de símbolos*/
void IMPRIMIR();

entrada BUSCAR(char *lex);
#endif

#ifndef TSIM_H_
#define TSIM_H_

typedef struct {
    char* lexema;
    double valor;
} entrada;

/*Inserta una entrada en la tabla de símbolos y
 * devuelve el tipo de componente
 */
double NUEVA_ENTRADA(char *lexema, double valor);

/*Crea la tabla de símbolos con las palabras reservadas del lenguaje*/
void CREAR_TABLA();

/*Imprime el contenido de la tabla de símbolos*/
void IMPRIMIR();

entrada BUSCAR(char *lex);
#endif

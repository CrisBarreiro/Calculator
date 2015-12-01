/*
 * help.c
 *
 *  Created on: 1 de dic. de 2015
 *      Author: cristina
 */

#include <stdio.h>
#include <stdlib.h>

void HELP() {
	printf("Calculadora de propósito general por línea de comandos. Dispone de varios modos de funcionamiento.\n");
	printf("\t* Modo interactivo. Permite la introducción de comandos que ejecuten operaciones por parte del usuario. Para lanzar el programa en este modo, no es necesario introducir parámetros adicionales: ./calculator\n");
	printf("\n");
	printf("\t* Modo lectura desde fichero. Permite la ejecución de operaciones matemáticas contenidas en un fichero. Para lanzar el programa en este modo, debe indicarse la ruta del fichero de operaciones, de la siguiente manera: './calculator [nombre de archivo]'. Ejemplo: ./calculator operaciones.txt\n");
	printf("\n");
	printf("\t* Modo manual reducido. Muestra al usuario una pequeña descripción del programa y sus modos de funcionamiento. Para lanzarlo, es necesarario hacerlo del siguiente modo: './calculator -h'\n");
	printf("\n");
	printf("\t* Modo manual completo. Muestra por pantalla el manual completo de usuario. Para lanzarlo, es necesario hacerlo del siguiente modo: './calculator --help'\n");
}

void COMPLETE_HELP() {
	printf("./calculator [OPCIONES] [ARCHIVO]\n");
	printf("\n");

	printf("OPCIONES\n");
	printf("\t-h: Muestra el manual de usuario reducido\n");
	printf("\t\t./calculator -h\n");
	printf("\t--help: Muestra el manual de usuario completo\n");
	printf("\t\t./calculator --help\n");
	printf("\t[archivo]: Carga los comandos incluidos en un archivo\n");
	printf("\t\t./calculator archivo.txt\n");
	printf("\tmodo por defecto: Se carga una línea de comandos interactiva\n");
	printf("\t\t./calculator\n");
	printf("\n");

	printf("EJECUCIÓN DE COMANDOS\n");
	printf("\n");
	printf("Tras haber insertado un comando, es necesario pulsar ENTER para ejecutarlo.\n");
	printf("\n");

	printf("MODOS DE EJECUCIÓN\n");
	printf("\n");
	printf("El programa cuenta con dos modos de ejecución. Por defecto, la salida del comando introducido se imprime a la salida estándar. No obstante, es posible evitar que la salida se imprima, insertando un punto y coma ';' al final del comando. Ejemplo: 2+4;\n");
	printf("\n");

	printf("OPERACIONES ARITMÉTICAS\n");
	printf("\n");
	printf("Este programa soporta las siguientes operaciones aritméticas:\n");
	printf("\n");
	printf("\tSuma ('+'). Ejemplo: 2+4\n");
	printf("\tResta ('-'). Ejemplo: 2-4\n");
	printf("\tMultiplicación ('*'). Ejemplo: 2*4\n");
	printf("\tDivisión ('/'). Ejemplo: 2/4\n");
	printf("\tPotencia('^'). Ejemplo: 2^4\n");
	printf("Estas operaciones pueden ser realizadas sin necesidad de asignar su resultado a ninguna variable.\n");
	printf("\n");

	printf("ASIGNACIÓN DE VARIABLES\n");
	printf("\n");
	printf("Este programa soporta el uso de variables definidas por el usuario.\n");
	printf("Para inicializar una variable, deberá asignársele un valor, para lo que se utilizará el símbolo igual ('='). Ejemplo: a = 2 + 4. La variable tomará el valor de la expresión situada después del símbolo igual ('='), en este caso, 6. La asignación de variables se producirá siempre que la expresión situada a la derecha del símbolo igual ('=') tenga algún valor, en otro caso, se producirá un error.\n");
	printf("\n");
	printf("Una variable puede asignarse a los siguientes elementos:\n");
	printf("\tUn número\n");
	printf("\tUna variable\n");
	printf("\tUna operación aritmética realizada sobre un conjunto de números y/o variables\n");
	printf("\tUna función aplicada sobre un número o variable\n");
	printf("\n");

	printf("USO DE CONSTANTES\n");
	printf("\n");
	printf("El programa permite el uso de constantes matemáticas predefinidas. Las constantes disponibles son:\n");
	printf("\te: \tNúmero de Euler.\t2.71828\n");
	printf("\tpi:\tNúmero Pi.\t\t3.14159\n");
	printf("El valor de una constante puede ser impreso, o usarse en expresiones matemáticas. En este último caso, sólo pueden usarse después del signo igual ('=') de la expresión, ya que su valor no puede ser sobreescrito. Ejemplo: a = 2 * pi\n");
	printf("\n");

	printf("FUNCIONES\n");
	printf("\n");
	printf("El programa incluye por defecto varias funciones pertenecientes a la librería 'math.h' del lenguaje C. Las funciones disponibles son las siguientes:\n");
	printf("\tsqrt\traíz cuadrada\n");
	printf("\tsin\tseno\n");
	printf("\tcos\tcoseno\n");
	printf("\ttan\ttangente\n");
	printf("\tasin\tarco seno\n");
	printf("\tacos\tarco coseno\n");
	printf("\tatan\tarco tangente\n");
	printf("\tsinh\tseno hiperbólico\n");
	printf("\tcosh\tcoseno hiperbólico\n");
	printf("\ttanh\ttangente hiperbólica\n");
	printf("\tceil\tredondea al siguiente entero\n");
	printf("\tfloor\ttrunca el parámetro recibido\n");
	printf("\tfabs\tvalor absoluto\n");
	printf("\tlog\tlogaritmo neperiano\n");
	printf("\tlog10\tlogaritmo en base 10\n");
	printf("\texp\tfunción exponencial\n");
	printf("\n");
	printf("Todas las funciones reciben un único parámetro, que puede ser un número, una variable, una constante, o una operación aritmética. Los parámetros deben ser pasados entre paréntesis '(' ')'. Ejemplo: sin (pi/2)\n");
	printf("\n");

	printf("COMANDOS ESPECIALES\n");
	printf("\n");
	printf("El programa dispone de una serie de comandos especiales que pueden ser ejecutados por los usuarios:\n");
	printf("\thelp\t\tmuestra el manual de usuario\n");
	printf("\texit\t\tfinaliza el programa\n");
	printf("\tvariables\timprime la lista de variables definidas\n");
	printf("\tconstants\timprime la lista de constantes predeterminadas\n");
	printf("\tfunctions\timprime la lista de funciones disponibles\n");
	printf("\n");

}

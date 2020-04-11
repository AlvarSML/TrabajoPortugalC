/*----------------------------------------------+
|Nombre:   TrabajoPortugal.c                    |
|Sinopsis: Tratamiento de datos de un archivo   |
| csv                                        |
|Descripción:                                   |
|                                    |
|Directivas de compilación: compilador gcc      |
|Lista de códigos de salida del programa:       |
|  Devuelve 0.                                  |
|Organización: Universidad de Burgos            |
|Autor:   Alvar San Martin                      |
|Fecha:   11/04/2020                            |
|Versión: v1.0                                  |
+----------------------------------------------*/

#include <stdio.h>

int solicitarOpcionMenu();
void seleccionarOpcion(int);
int contarCaracteres(FILE *);
int filaMasLarga(FILE *);
void resultadosPartido(FILE *);
int insertarFilas(FILE *);
_Bool validarEntero(int, int, int, int, char);
int contarFilas(FILE *);
int limpiarBuffer();

int main(void) {
  printf("Hello World\n");
  solicitarOpcionMenu();
  //system("clear");
  return 0;
}

/*
* Muestra el menu y solicita una opcion
* @return opcion seleccionada
*/
int solicitarOpcionMenu(){
  int opt;

  printf("*****************************************\n");
  printf("*     Bienvenido al tratamiento del     *\n");
  printf("*     fichero 'Elecciones en Portugal'  *\n");
  printf("*****************************************\n\n");
  printf("\t1.- Numero de caractes totales\n");
  printf("\t2.- Fila mas larga\n");
  printf("\t0.- Salir\n\n");
  printf("Introduzca una opcion > ");
  
  scanf("%i",&opt);

  system("clear");

  if (opt > 2 || opt < 0) {
    printf("! Valor incorrecto, introduce un valor entre 0 y 2");
  } else return opt;
  
}

/*
* Llama a las funciones que ejecutan cada una de las opciones 
* del menú mediante un switch. Abrir y cerrar el fichero desde aquí y  
* pasarlo ya abierto
* @param opcion del menu
*/
void seleccionarOpcion(int opcion) {

}


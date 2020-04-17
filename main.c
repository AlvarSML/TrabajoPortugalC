/*----------------------------------------------+
|Nombre:   TrabajoPortugal.c                    |
|Sinopsis: Tratamiento de datos de un archivo   |
| csv                                           |  
|Descripción:                                   |
|                                               |
|Directivas de compilación: compilador gcc      |
|Lista de códigos de salida del programa:       |
|  Devuelve 0.                                  |
|Organización: Universidad de Burgos            |
|Autor:   Alvar San Martin                      |
|Fecha:   11/04/2020                            |
|Versión: v1.0                                  |
+----------------------------------------------*/

#include <stdio.h>
#include <stdbool.h>

#define SUPERIOR 2
#define INFERIOR 0
#define INTRO 10

/*
* Prototipado de funciones
*/

int solicitarOpcionMenu();
void seleccionarOpcion(int);
int contarCaracteres(FILE *);
int filaMasLarga(FILE *);
int contarFilas(FILE *);
void resultadosPartido(FILE *);
int insertarFilas(FILE *);
bool validarEntero(int, int, int, int, char);
int contarFilas(FILE *);
int limpiarBuffer();

int main(void) {
  int opt;

  solicitarOpcionMenu();
  seleccionarOpcion(opt);

  //system("clear");
  return 0;
}

/*
* Muestra el menu y solicita una opcion
* @return opcion seleccionada
*/
int solicitarOpcionMenu(){
  int opt = 1, params;
  
  printf("*****************************************\n");
  printf("*     Bienvenido al tratamiento del     *\n");
  printf("*     fichero 'Elecciones en Portugal'  *\n");
  printf("*****************************************\n\n");

  while (opt != 0 || opt > 2 || opt < 0) {
    printf("\t1.- Numero de caractes totales\n");
    printf("\t2.- Fila mas larga\n");
    printf("\t0.- Salir\n\n");
    printf("Introduzca una opcion > ");
    
    params = scanf("%i",&opt);

    system("clear");

    if (!validarEntero(opt, SUPERIOR, INFERIOR, params, getchar())) {
      printf("! Valor incorrecto, introduce un valor entre 0 y 2\n");
    } else return opt;
  }

  return -1;
}

/*
* Llama a las funciones que ejecutan cada una de las opciones 
* del menú mediante un switch. Abrir y cerrar el fichero desde aquí y  
* pasarlo ya abierto
* @param opcion del menu
*/
void seleccionarOpcion(int opcion) {
  FILE * f;
  switch(opcion) {
    case 1:
      f = fopen("elecciones.csv", "r");
      printf("La fila mas larga es la: ",filaMasLarga(f));

      fclose(f);
      break;
    case 2:
      break;
    case 0:
      break;
    //default:

  }
}

/*
* Valida un numerod del menu
* @param numero leido
* @param limite superior
* @param limite inferior
* @param parametros leidos por el scanf
* @param valor del intro en el scanf
* @return si el valor es valido o no
*/
bool validarEntero(int num, int sup, int inf, int params, char intro) {

  if (num > sup || num < inf || params < 1 || intro != (char)INTRO) {
    return false;
  } else {
    return true;
  }

}

/* 
* Limpiarbuffer
* @return 
*/
int limpiarBuffer() {
  //clean_stdin();
  return 0;
}

/*
* busca la fila mas larga, muestra el numero de caracteres y las filas totales
*/
int filaMasLarga(FILE * f) {
  int masLarga = 0;
  int nlinea = 0;
  int caracteres = 0;
  int maxCaracteres;
  char c;

  while ((c = fgetc(f)) != EOF) {
    caracteres++;
    if (c == '\n') {
      if (maxCaracteres<caracteres){
        masLarga = nlinea;
        maxCaracteres = caracteres;
      } 
      caracteres = 0;
      nlinea ++;
    }
  }

  printf("Maximo de caracteres %i\",maxCaracteres);
  return masLarga;
}

int contarFilas(FILE * f) {
  return 0;
}

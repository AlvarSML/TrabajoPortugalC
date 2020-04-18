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
|Versión: v1.1                                  |
+----------------------------------------------*/

#include <stdbool.h>
#include <stdio.h>

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

  opt = solicitarOpcionMenu();
  seleccionarOpcion(opt);

  // system("clear");

  return 0;
}

// asda
/*
 * Muestra el menu y solicita una opcion
 * @return opcion seleccionada
 */
int solicitarOpcionMenu() {
  int opt = 1, params;

  printf("*****************************************\n");
  printf("*     Bienvenido al tratamiento del     *\n");
  printf("*     fichero 'Elecciones en Portugal'  *\n");
  printf("*****************************************\n\n");

  while (opt != 0 || opt > 2 || opt < 0) {
    printf("\t1.- Numero de caractes totales\n");
    printf("\t2.- Fila mas larga\n");
    printf("\t3.- Resultados de un partido por regiones\n");
    printf("\t4.- Inserccion simple\n");
    printf("\t0.- Salir\n\n");
    printf("Introduzca una opcion > ");

    params = scanf("%i", &opt);

    // system("clear");

    if (!validarEntero(opt, SUPERIOR, INFERIOR, params, getchar())) {
      printf("! Valor incorrecto, introduce un valor entre 0 y 2\n");
    } else
      return opt;
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
  FILE *f;
  switch (opcion) {
    case 2:
      f = fopen("elecciones.csv", "r");
      printf("La fila mas larga es la: %i \n", filaMasLarga(f));

      fclose(f);
      break;
    case 1:
      f = fopen("elecciones.csv", "r");
      printf("Hay %i caracteres \n",contarCaracteres(f));
      fclose(f);
      break;
    case 3:
      
      break;
    case 4:
      break;
    case 0:
      break;
      // default:
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
  // clean_stdin();
  return 0;
}

/*
 * Busca la fila mas larga, muestra el numero de caracteres y las filas totales
 * @param archivo a leer
 * @return numero de la fila mas larga
 * 
 */
int filaMasLarga(FILE *f) {
  int masLarga = 1;
  int nlinea = 1;
  int caracteres = 0;
  int maxCaracteres;
  char c;

  while ((c = fgetc(f)) != EOF) {
    caracteres++;
    if (c == '\n') {
      if (maxCaracteres < caracteres) {
        masLarga = nlinea;
        maxCaracteres = caracteres;
      }
      caracteres = 0;
      nlinea++;
    }
  }

  if (maxCaracteres < caracteres) {
    masLarga = nlinea;
    maxCaracteres = caracteres;
  }

  printf("Maximo de caracteres %i\n", maxCaracteres);
  return masLarga;
}

/*
 * Cuenta el numer de filas de un archivo (solo si hay mas de 1)
 * @param archivo a leer
 * @return numero de filas
 */
int contarFilas(FILE *f) {
  int nFilas = 1;
  char c;

  while ((c = fgetc(f)) != EOF) {
    if (c == '\n') {
      nFilas ++;
    }
  }

  return nFilas;
}

/*
* Cuenta el numero de caracteres de un archivo
* @param archivo a leer
* @return numero de caracteres
*/
int contarCaracteres(FILE *f) {
  int nCaracteres = 0;
  char c;

  while ((c = fgetc(f)) != EOF) {
    if (c != '\n') {
      nCaracteres++;
    }
  }

  return nCaracteres;
}

/*
* Muestra los resultados de un partido por region
* @param archivo a leer
*/
void resultadosPartido(FILE *f){
  printf("Introduce un partido: \n");
  printf("\t1.- PS\n");
  printf("\t2.- PPD/PSD\n");
  printf("\t3.- B.E.\n");
  printf("\t4.- CDS-PP\n");
  printf("\t5.- PCP-PEV\n");
  printf("\t5.- PAN\n");
  printf("\t7.- CH\n");
  printf("\t8.- R.I.R\n");
  printf("\t9.- PCTP/MRPP\n");
  printf("\t10.- A\n");
  printf("\t11.- L\n");
  printf("\t12.- IL\n");
  printf("\t13.- JPP\n");
  printf("\t14.- NC\n");
  printf("\t15.- PDR\n");
  printf("\t16.- PNR\n");
  printf("\t17.- PURP\n");
  printf("\t18.- PPM\n");
  printf("\t19.- MPT\n");
  printf("\t20.- PTP\n");
  printf("\t21.- PTP\n");
}


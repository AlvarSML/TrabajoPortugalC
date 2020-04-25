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
#include <string.h>

#define SUPERIOR 4
#define INFERIOR 0
#define INTRO 10

#define SUPERIORINT 10000
#define SUPERIORPORCIENTO 100

#define SUPERIORPART 21
#define INFERIORPART 1

#define MAXCHAR 20

#define MAXPARTIDO 10
#define NPARTIDOS 21

#define LETRASTERRITORIO 20
#define LETRASPARTIDO 11

#define ARCHIVO "Elecciones.csv"

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

  do {
    opt = solicitarOpcionMenu();
    seleccionarOpcion(opt);
    printf("[Pulsa INTRO para continuar]\n");
    limpiarBuffer();
  } while (opt != 0);
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

  while (opt != 0) {
    printf("\t1.- Numero de caractes totales\n");
    printf("\t2.- Fila mas larga\n");
    printf("\t3.- Resultados de un partido por regiones\n");
    printf("\t4.- Inserccion simple\n");
    printf("\t0.- Salir\n\n");
    printf("Introduzca una opcion > ");

    params = scanf("%i", &opt);

    // system("clear");

    if (!validarEntero(opt, SUPERIOR, INFERIOR, params, getchar())) {
      printf("! Valor incorrecto, introduce un valor entre %i y %i\n", INFERIOR,
             SUPERIOR);

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
      f = fopen(ARCHIVO, "r");
      printf("La fila mas larga es la: %i \n", filaMasLarga(f));

      fclose(f);
      break;
    case 1:
      f = fopen(ARCHIVO, "r");
      printf("Hay %i caracteres \n", contarCaracteres(f));
      fclose(f);
      break;
    case 3:
      f = fopen(ARCHIVO, "r");
      resultadosPartido(f);
      fclose(f);
      break;
    case 4:
      f = fopen(ARCHIVO, "rw");
      insertarFilas(f);
      fclose(f);
      break;
    case 0:
      break;
      // default:
  }
}

/*
 * Valida un numero del menu
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
 * Valida un numero decimal (float), para evitar el redondeo de float a int
 * @param numero leido
 * @param limite superior
 * @param limite inferior
 * @param parametros leidos por el scanf
 * @param valor del intro en el scanf
 * @return si el valor es valido o no
 */
bool validarDecimal(float num, int sup, int inf, int params, char intro) {
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
  while (getchar() != '\n') return 1;
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
      nFilas++;
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
void resultadosPartido(FILE *f) {
  int opt, params;
  int instante, blancos, subs, elegidos, votos, hondt, estimados, desc;
  char territorio[20], partido[11];
  float porcentaje, validos;

  const char PARTIDOS[NPARTIDOS][MAXPARTIDO] = {
      "PS",    "PPD/PSD",   "B.E.", "CDS-PP", "PCP-PEV", "PAN", "CH",
      "R.I.R", "PCTP/MRPP", "A",    "L",      "IL",      "JPP", "NC",
      "PDR",   "PNR",       "PURP", "PPM",    "MPT",     "PTP", "MAS"};
  do {
    do {
      printf("Introduce un partido: \n");

      for (int i = 0; i < NPARTIDOS; i++) {
        printf("%i.- %s\n", (i + 1), PARTIDOS[i]);
      }
      printf("0.- Salir\n");

      printf("> ");
      params = scanf("%i", &opt);

    } while (
        !validarEntero(opt, SUPERIORPART, INFERIORPART, params, getchar()) &&
        opt != 0);

    if (opt != 0) {
      printf(
          "Instante\tTerritorio\t\tBlancos\tSubscritos\tElegidos\tPorcentaje\tV"
          "al"
          "id"
          "os\t\t"
          "Voto"
          "s\tD'Hont\tEstimados\n");

      rewind(f);

      while (fscanf(f, "%i,%20[^,],%i,%i,%i,%11[^,],%i,%f,%f,%i,%i,%i",
                    &instante, territorio, &blancos, &subs, &elegidos, partido,
                    &desc, &porcentaje, &validos, &votos, &hondt,
                    &estimados) != EOF) {
        if (strcmp(partido, PARTIDOS[opt - 1]) == 0) {
          printf("%i\t\t%s\t%i\t%i\t\t%i\t\t%f\t%f\t%i\t%i\t%i\n", instante,
                 territorio, blancos, subs, elegidos, porcentaje, validos,
                 votos, hondt, estimados);
        }
      }

      printf("[Pulsa INTRO para continuar]\n");
      limpiarBuffer();
    }
  } while (opt != 0);
}

/*
 * Inserta filas en el archivo para el instante elegifo
 * @param
 * @return
 */
int insertarFilas(FILE *f) {
  int filas, params, blancos, nulos, subs, instante, total, hondt, objetivo, selecPartido, selecTerri;
  char opt;
  char territorio[LETRASTERRITORIO], partido[LETRASTERRITORIO];
  float elegidos, validos, votos;

  int incFilas = 0;

  do {
    filas = contarFilas(f);
    printf("-Se han cargado %i filas-\n", filas);

    printf("Introduce los siguientes datos: \n");
    printf("Instante de voto (0-3)[0]: ");
    params = scanf("%i", &instante);

    printf("Territorio:");
    // leer territorios
    do {
      printf("Votos BLANCOS (0-10000): ");
      params = scanf("%i", &blancos);
    } while (!validarEntero(blancos, SUPERIORINT, INFERIOR, params, getchar()));

    do {
      printf("Votos NULOS (0-10000): ");
      params = scanf("%i", &nulos);
    } while (!validarEntero(nulos, SUPERIORINT, INFERIOR, params, getchar()));

    do {
      printf("Subscritos (0-10000): ");
      params = scanf("%i", &subs);
    } while (!validarEntero(subs, SUPERIORINT, INFERIOR, params, getchar()));

    printf("Partido: ");
    // leer partidos
    do {
      printf("Elegidos (porcentaje con decimales) (0-100): ");
      params = scanf("%f", &elegidos);
    } while (!validarDecimal(subs, SUPERIORPORCIENTO, INFERIOR, params, getchar()));

    do {
      printf("Porcenataje de votos (0-100): ");
      params = scanf("%f", &votos);
    } while (!validarDecimal(votos, SUPERIORPORCIENTO, INFERIOR, params, getchar()));

    do {
      printf("Porcentaje de votos validos (porcentaje con decimales) (0-100): ");
      params = scanf("%f", &validos);
    } while (!validarDecimal(validos, SUPERIORPORCIENTO, INFERIOR, params, getchar()));

    do {
      printf("Total de votos validos (0-10000): ");
      params = scanf("%i", &total);
    } while (!validarEntero(total, SUPERIORINT, INFERIOR, params, getchar()));

    do {
      printf("Elegidos (Hondt) (0-100): ");
      params = scanf("%i", &hondt);
    } while (!validarEntero(hondt, SUPERIORPORCIENTO, INFERIOR, params, getchar()));

    do {
      printf("Objetivo de elegidos (0-100): ");
      params = scanf("%i", &objetivo);
    } while (!validarEntero(objetivo, SUPERIORPORCIENTO, INFERIOR, params, getchar()));

        fprintf("%i,%20[^,],%i,%i,%i,%11[^,],%i,%f,%f,%i,%i,%i", instante,
                territorio[selecTerri], blancos, nulos, subs, partido[selecPartico], elegidos, validos,
                votos, total, hondt, objetivo);

    printf("¿Introducir otra fila? (s/n)[N]: ");
    params = scanf("%c", &opt);

    if (opt == 's' || opt == 'S') filas++;

  } while (opt == 's' || opt == 'S');

  printf("Se han añadido %i filas\n", incFilas);
  return incFilas;
}
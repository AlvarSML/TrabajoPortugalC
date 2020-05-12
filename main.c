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
|Versión: v0.7                                  |
|Repositorio:                                   |
|  https://github.com/alvarsnow/TrabajoPortugalC|
+----------------------------------------------*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define SUPERIOR 6
#define INFERIOR 0
#define INTRO 10

#define SUPERIORINT 10000
#define SUPERIORPORCIENTO 100

#define SUPERIORPART 21
#define INFERIORPART 1

#define MAXCHAR 20

#define MAXPARTIDO 10
#define NPARTIDOS 21

#define NREGIONES 20
#define MAXREGION 19

#define LETRASTERRITORIO 20
#define LETRASPARTIDO 11

#define ARCHIVO "Elecciones.csv"

/**
 * Globales
 */
const char PARTIDOS[NPARTIDOS][MAXPARTIDO] = {
    "PS",    "PPD/PSD",   "B.E.", "CDS-PP", "PCP-PEV", "PAN", "CH",
    "R.I.R", "PCTP/MRPP", "A",    "L",      "IL",      "JPP", "NC",
    "PDR",   "PNR",       "PURP", "PPM",    "MPT",     "PTP", "MAS"};

const char REGIONES[NREGIONES][MAXREGION] = {"Territorio Nacional",
                                             "Aveiro",
                                             "Beja",
                                             "Braga",
                                             "Bragansa",
                                             "Castelo Branco",
                                             "Coimbra",
                                             "Avora",
                                             "Faro",
                                             "Guarda",
                                             "Leiria",
                                             "Lisboa",
                                             "Madeira",
                                             "Portalegre",
                                             "Porto",
                                             "Santarom",
                                             "Setabal",
                                             "Viana do Castelo",
                                             "Vila Real",
                                             "Viseu"};

/**
 *  Structs
 */
struct Elec {
  int instante;                       // 1
  char territorio[LETRASTERRITORIO];  // 2
  int blancos;                        // 3
  int nulos;                          // 4          
  int subs;                           // 5
  char partido[LETRASPARTIDO];        // 6
  int elegidos;                       // 7
  float porcentaje;                   // 8    
  float validos;                      // 9
  float porcientoVotos;               // 10
  int hondt;                          // 11
  int totalElegidos;                  // 12
};

/**
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

void mostrarPartidos();
void mostrarRegiones();

// Semanas 4 y 5
int eliminarFilas(struct Elec[], int);
void calcularResultados(struct Elec[], int);

// Complementarias

// Carga un fichero de texto (entradao sin  filas repetidas)en el vector de
// registros
int cargarRegistros(struct Elec[], FILE *);
// marca con  -1 las  filas   del  vectorde registrosrepetidas
void escribeFicheroLimpio(struct Elec, FILE *);
/*escribe una  sola   ficla   no repetidaen depurado.csv*/
void escribeFicheroLimpio(struct Elec, FILE *);
/*escribe una  sola fila de resultados en el fichero binario*/
void escribirBinario(struct Elec, FILE *);
/*comparados   registros del  vector de  registros
                                 y devuelve cierto si son iguales*/
bool compararRegistros(struct Elec, struct Elec);
/*ecribeuna  sola   fila en un ficherode texto*/
void escribeFicheroLimpio(struct Elec, FILE *);
/*muestaun menúcon  todoslos territoriosparaelegir(1- 22)
                          el que  queremos*/

//#void inicializarVectorResultados(GANADOR[]); /*elvector de registros en  el
// que   guardaremos los resultados por territoriolo incializamos*/ #void
// resumenGanador(struct Elec[], GANADOR[], int); /*almacenamos en  el  vector
// de registros ganador los resultados por cada territorio*/ #void
// imprimirGanador(GANADOR[]); /* imprimimospor pantallalos datosdel ganadorde
// cadaterritorio * /

/***************************
 *      MAIN               *
 * ************************/
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

/**
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
    printf("\t5.- Depuracion del fichero\n");
    printf("\t6.- Resumen de resultados\n");
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

/**
 * Llama a las funciones que ejecutan cada una de las opciones
 * del menú mediante un switch. Abrir y cerrar el fichero desde aquí y
 * pasarlo ya abierto
 * @param opcion del menu
 */
void seleccionarOpcion(int opcion) {
  FILE *f;

  f = fopen(ARCHIVO, "r");
  int filas = contarFilas(f);
  struct Elec vector[filas];
  fclose(f);

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
      f = fopen(ARCHIVO, "a+");
      insertarFilas(f);
      fclose(f);
      break;
    case 5:
      f = fopen(ARCHIVO, "r");
      cargarRegistros(vector, f);
      fclose(f);
      break;
    case 6:
      break;
    case 0:
      break;
      // default:
  }
}

/**
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

/**
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

/**
 * Limpiarbuffer
 * @return
 */
int limpiarBuffer() {
  // clean_stdin();
  while (getchar() != '\n')
    ;
  return 1;
}

/**
 * Busca la fila mas larga, muestra el numero de caracteres y las filas totales
 * @param archivo a leer
 * @return numero de la fila mas larga
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

/**
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

/**
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

/**
 * Muestra por pantalla los partidos con su numero
 */
void mostrarPartidos() {
  for (int i = 0; i < NPARTIDOS; i++) {
    printf("%i.- %s\n", (i + 1), PARTIDOS[i]);
  }
}

/**
 * Muestra por pantalla las regiones con su numero
 */
void mostrarRegiones() {
  for (int i = 0; i < NREGIONES; i++) {
    printf("%i.- %s\n", (i + 1), REGIONES[i]);
  }
}

/**
 * Muestra los resultados de un partido por region
 * @param archivo a leer
 */
void resultadosPartido(FILE *f) {
  int opt, params;
  int instante, blancos, subs, elegidos, votos, hondt, estimados, desc;
  char territorio[20], partido[11];
  float porcentaje, validos;

  do {
    do {
      printf("Introduce un partido: \n");
      mostrarPartidos();
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

/**
 * Inserta filas en el archivo para el instante elegifo
 * @param f archivo en el que escrbir (necestita peromisos r y w)
 * @return numero de filas escritas
 */
int insertarFilas(FILE *f) {
  int filas = 1, params, blancos, nulos, subs, instante = 0, total, hondt,
      objetivo, selecPartido, selecTerri, territorio, partido;
  char opt;
  float elegidos, validos, votos;

  do {
    filas = contarFilas(f);
    printf("-Se han cargado %i filas-\n", filas);

    printf("Introduce los siguientes datos: \n");

    do {
      printf("Instante de voto (0-3): ");
      params = scanf("%i", &instante);
    } while (!validarEntero(instante, 3, INFERIOR, params, getchar()));

    do {
      printf("Territorio:\n");
      mostrarRegiones();
      printf("(1-21)[1] > ");
      params = scanf("%i", &territorio);
    } while (
        !validarEntero(territorio, NREGIONES + 1, INFERIOR, params, getchar()));

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

    do {
      printf("Partido: \n");
      mostrarPartidos();
      printf("(1-22)[1] > ");
      params = scanf("%i", &partido);
    } while (
        !validarEntero(partido, NPARTIDOS + 1, INFERIOR, params, getchar()));

    do {
      printf("Elegidos (porcentaje con decimales) (0-100): ");
      params = scanf("%f", &elegidos);
    } while (!validarDecimal(elegidos, SUPERIORPORCIENTO, INFERIOR, params,
                             getchar()));

    do {
      printf("Porcenataje de votos (0-100): ");
      params = scanf("%f", &votos);
    } while (
        !validarDecimal(votos, SUPERIORPORCIENTO, INFERIOR, params, getchar()));

    do {
      printf(
          "Porcentaje de votos validos (porcentaje con decimales) (0-100): ");
      params = scanf("%f", &validos);
    } while (!validarDecimal(validos, SUPERIORPORCIENTO, INFERIOR, params,
                             getchar()));

    do {
      printf("Total de votos validos (0-10000): ");
      params = scanf("%i", &total);
    } while (!validarEntero(total, SUPERIORINT, INFERIOR, params, getchar()));

    do {
      printf("Elegidos (Hondt) (0-100): ");
      params = scanf("%i", &hondt);
    } while (
        !validarEntero(hondt, SUPERIORPORCIENTO, INFERIOR, params, getchar()));

    do {
      printf("Objetivo de elegidos (0-100): ");
      params = scanf("%i", &objetivo);
    } while (!validarEntero(objetivo, SUPERIORPORCIENTO, INFERIOR, params,
                            getchar()));

    fprintf(f, "%d,%s,%d,%d,%d,%s,%f,%f,%f,%d,%d,%d\n", instante,
            REGIONES[territorio], blancos, nulos, subs, PARTIDOS[partido],
            elegidos, validos, votos, total, hondt, objetivo);

    printf("¿Introducir otra fila? (s/n)[N]: ");
    params = scanf("%c", &opt);

    if (opt == 's' || opt == 'S') filas++;

  } while (opt == 's' || opt == 'S');

  printf("Se han añadido %i filas\n", filas);
  return filas;
}

/**
 * Crea un fichero de salida con las filas que no esten repetidas
 * @param Elec array de las filas del csv
 * @param int numero de filas
 * @return
 */
int eliminarFilas(struct Elec filas[], int nFilas) {}

/**
 * Calcula los resultados y los buelca en un ficero binario
 * @param Elec array de filas
 * @param numero de filas
 */
void calcularResultados(struct Elec filas[], int nfilas) {}

/** Carga un fichero de texto (entradao sin  filas repetidas)en el vector de
 * registros
 * @param filas vector de registros
 * @param archivo archivo abierto a cargar
 */
int cargarRegistros(struct Elec filas[], FILE *f) {
  rewind(f); //Para asegurarse que empezamos por el principip
  int i = 0;

  while (!feof(f)) {
    i++;
    fscanf(f, "%i,%20[^,],%i,%i,%i,%11[^,],%i,%f,%f,%i,%i,%i",
           &filas[i].instante, filas[i].territorio, &filas[i].blancos,
           &filas[i].nulos, &filas[i].subs, filas[i].partido, &filas[i].elegidos,
           &filas[i].porcentaje, &filas[i].validos, &filas[i].porcientoVotos,
           &filas[i].hondt, &filas[i].totalElegidos);
  }

  printf("->Se han cargado %i filas en el vector de registros\n", i);

  return i;
}

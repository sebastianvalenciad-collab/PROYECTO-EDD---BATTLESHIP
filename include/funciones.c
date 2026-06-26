#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include <string.h>

// Prototipo de funciones
int posicion_valida(int x, int y);
int puede_colocar_barco(Mapa *mapa, int x, int y, int largo, char orientacion);
void colocar_barco(Mapa *mapa, int x, int y, int largo, char orientacion);
void ubicar_barcos_jugador(TipoJugador *jugador);
void ubicar_barcos_ia(TipoJugador *ia);
void mostrar_mapa(Mapa mapa);

// Verifica si una posicion (x,y) pertenece al tablero y se ecnuyentra dentro de los limites del tablero.
int posicion_valida(int x, int y)
{
    return x >= 0 && x < N && y >= 0 && y < N;
}

// Verifica si un barco puede ser ubicado en la posicion (x,y) del tablero
int puede_colocar_barco(Mapa *mapa, int x, int y, int largo, char orientacion)
{
    // Recorre todas las casillas que ocupara el barco
    for(int i = 0; i < largo; i++)
    {
        int nx = x;
        int ny = y;

        // Calcula la sgte pos segun la orientacion del barco
        if(orientacion == 'H' || orientacion == 'h')
            ny = y + i;
        else if(orientacion == 'V' || orientacion == 'v')
            nx = x + i;
        else
            return 0;

        // Verifica que la casilla este libre
        if(!posicion_valida(nx, ny))
            return 0;

        if(mapa->matriz[nx][ny] != LIBRE)
            return 0;
    }

    return 1; // todas las posiciones son validas
}

// coloca un barco en el tablero
void colocar_barco(Mapa *mapa, int x, int y, int largo, char orientacion)
{
    // rEcorre todas las posiciones que ocupara el barco en el tablero.
    for(int i = 0; i < largo; i++)
    {
        int nx = x;
        int ny = y;

        // calcula la sgte posicion segun la orientacion del barco
        if(orientacion == 'H' || orientacion == 'h')
            ny = y + i;
        else
            nx = x + i;

        // marca la casilla como ocupada por un barco
        mapa->matriz[nx][ny] = BARCO;
    }
}

// Muestra por pantalla el tablero del jugador.
void mostrar_mapa(Mapa mapa)
{
    // printea los encabezados de las columnas
    printf("   A B C D E F G H I J\n");

    // recorre todas las filas del tablero
    for(int i = 0; i < N; i++)
    {
        // printea el numero de la fila
        printf("%2d ", i + 1);

        // recorre todas las columnas de la fila
        for(int j = 0; j < N; j++)
        {
            // si la casilla contiene un barco, muestra B
            if(mapa.matriz[i][j] == BARCO)
                printf("B ");
            else
                printf("- "); // muestra - en caso contrario
        }

        // salto de linea al final de cada fila
        printf("\n");
    }
}


// permite al jugador ubicar manualmente sus barcos en el tablero
void ubicar_barcos_jugador(TipoJugador *jugador)
{
    int largos[MAX_BARCOS] = {5, 4, 3, 3, 2};
    int fila;
    char columnaLetra;
    int columna;
    char orientacion;

    jugador->vidaTotal = 0;

    for(int i = 0; i < MAX_BARCOS; i++)
    {
        int colocado = 0;

        while(colocado == 0)
        {
            char entradaColumna[10];
            char entradaOrientacion[10];

            system("clear");

            puts("=================================");
            puts("      UBICACION DE BARCOS");
            puts("=================================");

            mostrar_mapa(jugador->tablero);

            printf("\nBarco %d de %d | Largo: %d\n", i + 1, MAX_BARCOS, largos[i]);

            printf("Ingrese columna inicial A-J: ");
            scanf(" %9s", entradaColumna);

            if(strlen(entradaColumna) != 1)
            {
                puts("\nColumna invalida. Debe ingresar solo una letra entre A y J.");
                puts("Presione ENTER para continuar...");
                getchar();
                getchar();
                continue;
            }

            columnaLetra = entradaColumna[0];

            if(columnaLetra >= 'A' && columnaLetra <= 'J')
                columna = columnaLetra - 'A';
            else if(columnaLetra >= 'a' && columnaLetra <= 'j')
                columna = columnaLetra - 'a';
            else
            {
                puts("\nColumna invalida. Debe ingresar una letra entre A y J.");
                puts("Presione ENTER para continuar...");
                getchar();
                getchar();
                continue;
            }

            printf("Ingrese fila inicial 1-10: ");
            if(scanf("%d", &fila) != 1)
            {
                puts("\nFila invalida. Debe ingresar un numero entre 1 y 10.");

                while(getchar() != '\n');

                puts("Presione ENTER para continuar...");
                getchar();
                continue;
            }

            printf("Ingrese orientacion H/V: ");
            scanf(" %9s", entradaOrientacion);

            if(strlen(entradaOrientacion) != 1)
            {
                puts("\nOrientacion invalida. Debe ingresar solo H o V.");
                puts("Presione ENTER para continuar...");
                getchar();
                getchar();
                continue;
            }

            orientacion = entradaOrientacion[0];

            if(orientacion != 'H' && orientacion != 'h' &&
               orientacion != 'V' && orientacion != 'v')
            {
                puts("\nOrientacion invalida. Debe ingresar H o V.");
                puts("Presione ENTER para continuar...");
                getchar();
                getchar();
                continue;
            }

            fila = fila - 1;

            if(puede_colocar_barco(&jugador->tablero, fila, columna, largos[i], orientacion))
            {
                colocar_barco(&jugador->tablero, fila, columna, largos[i], orientacion);

                // guarda las dimensiones segun la orientacion
                if(orientacion == 'H' || orientacion == 'h')
                {
                    jugador->barcos[i].ancho = largos[i];
                    jugador->barcos[i].largo = 1;
                }
                else
                {
                    jugador->barcos[i].ancho = 1;
                    jugador->barcos[i].largo = largos[i];
                }

                // informacion del abrco
                jugador->barcos[i].posX = fila;
                jugador->barcos[i].posY = columna;

                jugador->barcos[i].vida = largos[i];
                jugador->barcos[i].tamanio = largos[i];

                jugador->barcos[i].orientacion = orientacion;

                jugador->vidaTotal += largos[i]; // actualiza la vida total del jugador

                colocado = 1; // finaliza la ubicacion del barco
            }
            else
            {
                puts("\nUbicacion no valida. Intente nuevamente.");
            }

            puts("Presione ENTER para continuar...");
            getchar();
            getchar();
        }
    }
}


// ubica automaticamente los barcos de la ia
void ubicar_barcos_ia(TipoJugador *ia)
{
    // arreglo con el tamaño de los barcos
    int largos[MAX_BARCOS] = {5, 4, 3, 3, 2};

    // inicializa la vida total de la ia
    ia->vidaTotal = 0;

    // recorre todas los barcos que debe ubicar la ia
    for(int i = 0; i < MAX_BARCOS; i++)
    {
        int colocado = 0;

        // genera pos aleatorias hasta encontrar una valida
        while(colocado == 0)
        {
            int fila = rand() % N;
            int columna = rand() % N;
            char orientacion;

            if(rand() % 2 == 0) // selecciona aleatoriamente la orientacion del barco
                orientacion = 'H';
            else
                orientacion = 'V';

            // verifica si el barco puede ubicarse en la pos generada
            if(puede_colocar_barco(&ia->tablero, fila, columna, largos[i], orientacion))
            {
                // coloca el barco en el tbalero
                colocar_barco(&ia->tablero, fila, columna, largos[i], orientacion);

                // guarda las dimensiones segun la orientacion
                if(orientacion == 'H')
                {
                    ia->barcos[i].ancho = largos[i];
                    ia->barcos[i].largo = 1;
                }
                else
                {
                    ia->barcos[i].ancho = 1;
                    ia->barcos[i].largo = largos[i];
                }

                // info del barco
                ia->barcos[i].posX = fila;
                ia->barcos[i].posY = columna;
  
                ia->barcos[i].vida = largos[i];
                ia->barcos[i].tamanio = largos[i];
  
                ia->barcos[i].orientacion = orientacion;
  
                ia->vidaTotal += largos[i]; // actualiza la vida total de la ia
  
                colocado = 1;
            }
        }
    }
}

// Reduce la vida del barco que fue impactado por un disparo
void restar_vida_barco(TipoJugador *enemigo, int fila, int columna)
{
    // recorre todos los barcos del enemigo
    for(int i = 0; i < MAX_BARCOS; i++)
    {
        // recorre todas las casillas qwue ocupa el barco actual
        for(int j = 0; j < enemigo->barcos[i].tamanio; j++)
        {
            int bx = enemigo->barcos[i].posX;
            int by = enemigo->barcos[i].posY;

            // cacula la pos de cada parte del barco segun su orientacion
            if(enemigo->barcos[i].orientacion == 'H' || enemigo->barcos[i].orientacion == 'h')
                by = enemigo->barcos[i].posY + j;
            else
                bx = enemigo->barcos[i].posX + j;

            // verifica si la pos coincide con el disparo recibido
            if(bx == fila && by == columna)
            {
                enemigo->barcos[i].vida--; // reduce la vida del barco

                if(enemigo->barcos[i].vida == 0) // si la vida llega a cero el barco se hunde
                    puts("¡Barco hundido!");

                return; // finaliza la bisqieda al encontrar el barco hundido
            }
        }
    }
}

// funcion que permite al jugador realizar un disparo sobre el tablero enemigo
void disparar(TipoJugador *jugador, TipoJugador *enemigo)
{
    char letra;
    int fila;
    int columna;


    puts("\n==========================================================");
    printf("            ========= TURNO JUGADOR =========\n");
    puts("==========================================================");
    
    // pide la coordenada del disparo
    printf("\nIngrese la coordenada donde desea disparar. Ejemplo: A 5\n");
    printf("Disparo: ");
    scanf(" %c %d", &letra, &fila);
    
    // convierte la letra en el indice de la columna
    if(letra >= 'A' && letra <= 'J')
        columna = letra - 'A';
    else if(letra >= 'a' && letra <= 'j')
        columna = letra - 'a';
    else
    {
        puts("*** Columna invalida ***");
        return;
    }

    fila--; // ajusta la fila al indice de la matriz

    // verifica que la coord pertenezca al tablero
    if(fila < 0 || fila >= N || columna < 0 || columna >= N)
    {
        puts("*** Coordenada fuera del tablero ***");
        return;
    }

    // verifica que la pos no haya sido atacada anteriormente
    if(jugador->tableroAtaques.matriz[fila][columna] == AGUA ||
       jugador->tableroAtaques.matriz[fila][columna] == IMPACTO)
    {
        puts("Ya disparaste en esa posicion!");
        return;
    }

    // comprueba si el disparo impacto un barco enemigo
    if(enemigo->tablero.matriz[fila][columna] == BARCO)
    {
        puts("\n*** IMPACTO ***");

        // marca el impacto en ambos tabnleros
        jugador->tableroAtaques.matriz[fila][columna] = IMPACTO;
        enemigo->tablero.matriz[fila][columna] = IMPACTO;

        enemigo->vidaTotal--; // reduce la vida total del enemigo
 
        restar_vida_barco(enemigo, fila, columna); // reduce la vida especifica del barco
    }
    else
    {
        puts("\n*** Agua ***.");

        // registra el disparo como agua en el tablero
        jugador->tableroAtaques.matriz[fila][columna] = AGUA;

        // actualiza el tablero si la casilla estaba libre
        if(enemigo->tablero.matriz[fila][columna] == LIBRE)
            enemigo->tablero.matriz[fila][columna] = AGUA;
    }

    // vida restante del enemigo
    printf("Vida restante del enemigo: %d\n", enemigo->vidaTotal);
}

// realiza un disparo aleatorio de la ia
void disparo_aleatorio_ia(TipoJugador *ia, TipoJugador *jugador)
{
    int fila;
    int columna;
    int disparoValido = 0;

    // genera coords aleatorias hasta encontrar una casilla no utilizada
    while(disparoValido == 0)
    {
        fila = rand() % N;
        columna = rand() % N;

        if(ia->tableroAtaques.matriz[fila][columna] == LIBRE)
        {
            disparoValido = 1;
        }
    }

    // printea la coords donde dispara la ia
    printf("\nLa IA disparo en: %c %d\n", columna + 'A', fila + 1);

    // verifica si el disparo impacto el barco del jugador
    if(jugador->tablero.matriz[fila][columna] == BARCO)
    {
        puts("La IA acerto un disparo!");

        // marca el impacto en los tableros
        ia->tableroAtaques.matriz[fila][columna] = IMPACTO;
        jugador->tablero.matriz[fila][columna] = IMPACTO;

        jugador->vidaTotal--; // reduce la vida del barco impactado

        restar_vida_barco(jugador, fila, columna);
    }
    else
    {
        puts("La IA fallo el disparo!");

        ia->tableroAtaques.matriz[fila][columna] = AGUA; // registra el disparo como agua

        if(jugador->tablero.matriz[fila][columna] == LIBRE) // actualiza el tablero del jugador si la casila estaba ibre
        {
            jugador->tablero.matriz[fila][columna] = AGUA;
        }
    }
}

// ejecuta el turno de la ia en la dificultad media y facil
void ia_media(TipoJugador *ia, TipoJugador *jugador)
{
    disparo_aleatorio_ia(ia, jugador); // hace un disparo aleatorio
}

// MODO CAZADOR Y CAPTURA

typedef struct {
    int fila;
    int columna;
} CoordenadaIA;

CoordenadaIA candidatos[N * N];
int cantidadCandidatos = 0;
int fallosIA = 0;

// agrega una casilla candidata para el modo captura de la ia: la funcion verifica que la casilla se encuentre
// dentro de los limites del tablero y que no haya sido atacada con aterioridad. Si ambas condiciones se cumplen
// almacena la coord en el arreglo de candidatos para que pueda ser usada en los sgrtes disparos.
void agregar_candidato(int fila, int columna, TipoJugador *ia)
{
    // verifica que la pos este dentro del tablero
    if(fila < 0 || fila >= N || columna < 0 || columna >= N) return;

    // verifica que la casilla aun no haya sido atacada
    if(ia->tableroAtaques.matriz[fila][columna] != LIBRE) return;

    // agrega la pos al arreglo de los candidatos
    candidatos[cantidadCandidatos].fila = fila;
    candidatos[cantidadCandidatos].columna = columna;
    cantidadCandidatos++;
}

// agrega las casillas vecinas de un impacto al modo captura de la ia
void agregar_vecinos_ia(int fila, int columna, TipoJugador *ia)
{
    // agrega la casilla superioor,inferior,izquierda y derecha
    agregar_candidato(fila - 1, columna, ia);
    agregar_candidato(fila + 1, columna, ia);
    agregar_candidato(fila, columna - 1, ia);
    agregar_candidato(fila, columna + 1, ia);
}

// funcion que obtiene la sigfuiente coor para el modo cazador
void obtener_disparo_cazador(TipoJugador *ia, int *fila, int *columna)
{
    // recorre el tablero siguiendo el patron alternado x - x - x
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            // selecciona una casilla libre que pertenece al patron
            if((i + j) % 2 == 0 && ia->tableroAtaques.matriz[i][j] == LIBRE)
            {
                *fila = i;
                *columna = j;
                return;
            }
        }
    }
    // si no quedan casillas del patron selecciona una pos aleatoria
    do 
    {
        *fila = rand() % N;
        *columna = rand() % N;
    } 
        while(ia->tableroAtaques.matriz[*fila][*columna] != LIBRE);
}

// funcion que obtiene la pista para el modo dificil despues de varios intentos fallidos
void obtener_pista_barco(TipoJugador *jugador, TipoJugador *ia, int *fila, int *columna)
{
    // recorre todos los barcos del jugador
    for(int i = 0; i < MAX_BARCOS; i++)
    {
        // considera unicamente los barcos que siguen con vida
        if(jugador->barcos[i].vida > 0)
        {
            // recorre kas casukkas que ocupa el barco
            for(int j = 0; j < jugador->barcos[i].tamanio; j++)
            {
                int f = jugador->barcos[i].posX;
                int c = jugador->barcos[i].posY;

                // calcula la pos de cada parte del barco segun su orientacion
                if(jugador->barcos[i].orientacion == 'H' || jugador->barcos[i].orientacion == 'h')
                    c += j;
                else
                    f += j;

                if(ia->tableroAtaques.matriz[f][c] == LIBRE) // si la casilla aun no ha sido atacada, se utiliza como pista
                {
                    *fila = f;
                    *columna = c;
                    return;
                }
            }
        }
    }

    obtener_disparo_cazador(ia, fila, columna); // continua con el modo cazador
}

// esta funcion ejecuta la IA dificil, en modo cazador y modo captura
void ia_dificil(TipoJugador *ia, TipoJugador *jugador)
{
    int fila;
    int columna;

    // si exitsten pos candidatas continua en el modo captura
    if(cantidadCandidatos > 0)
    {
        cantidadCandidatos--;
        fila = candidatos[cantidadCandidatos].fila;
        columna = candidatos[cantidadCandidatos].columna;
    }
    else if(fallosIA >= 5) // si la ia acumula cinco fallos se obtiene una pista
    {
        obtener_pista_barco(jugador, ia, &fila, &columna);
        fallosIA = 0;
    }
    else // se continua la busqueda de barcos mediante el modo cazador
    {
        obtener_disparo_cazador(ia, &fila, &columna);
    }

    // muestra la coord del disparo realizado
    printf("\nLa IA disparo en: %c %d\n", columna + 'A', fila + 1);

    // verifica si el disparo impacto en algun barco
    if(jugador->tablero.matriz[fila][columna] == BARCO)
    {
        puts("La IA consiguio un impacto.");

        // actualñiza ambos tableros
        ia->tableroAtaques.matriz[fila][columna] = IMPACTO;
        jugador->tablero.matriz[fila][columna] = IMPACTO;

        jugador->vidaTotal--; // baja la vida del jugador y del barco impactado
        restar_vida_barco(jugador, fila, columna);

        fallosIA = 0; // reinicia el contadodr de fallos

        agregar_vecinos_ia(fila, columna, ia); // agrega las casillas vecinas para continuar en modo captura
    }
    else
    {
        puts("La IA fallo el disparo."); // registra el disparo como agua

        ia->tableroAtaques.matriz[fila][columna] = AGUA;

        if(jugador->tablero.matriz[fila][columna] == LIBRE) jugador->tablero.matriz[fila][columna] = AGUA;

        fallosIA++; // aumenta el contador de fallos
    }
}
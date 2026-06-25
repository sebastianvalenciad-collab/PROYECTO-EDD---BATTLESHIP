#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

int posicion_valida(int x, int y);
int puede_colocar_barco(Mapa *mapa, int x, int y, int largo, char orientacion);
void colocar_barco(Mapa *mapa, int x, int y, int largo, char orientacion);
void ubicar_barcos_jugador(TipoJugador *jugador);
void ubicar_barcos_ia(TipoJugador *ia);
void mostrar_mapa(Mapa mapa);


int posicion_valida(int x, int y)
{
    return x >= 0 && x < N && y >= 0 && y < N;
}

int puede_colocar_barco(Mapa *mapa, int x, int y, int largo, char orientacion)
{
    for(int i = 0; i < largo; i++)
    {
        int nx = x;
        int ny = y;

        if(orientacion == 'H' || orientacion == 'h')
            ny = y + i;
        else if(orientacion == 'V' || orientacion == 'v')
            nx = x + i;
        else
            return 0;

        if(!posicion_valida(nx, ny))
            return 0;

        if(mapa->matriz[nx][ny] != LIBRE)
            return 0;
    }

    return 1;
}

void colocar_barco(Mapa *mapa, int x, int y, int largo, char orientacion)
{
    for(int i = 0; i < largo; i++)
    {
        int nx = x;
        int ny = y;

        if(orientacion == 'H' || orientacion == 'h')
            ny = y + i;
        else
            nx = x + i;

        mapa->matriz[nx][ny] = BARCO;
    }
}

void mostrar_mapa(Mapa mapa)
{
    printf("   A B C D E F G H I J\n");

    for(int i = 0; i < N; i++)
    {
        printf("%2d ", i + 1);

        for(int j = 0; j < N; j++)
        {
            if(mapa.matriz[i][j] == BARCO)
                printf("B ");
            else
                printf("- ");
        }

        printf("\n");
    }
}

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
            system("clear");

            puts("=================================");
            puts("      UBICACION DE BARCOS");
            puts("=================================");

            mostrar_mapa(jugador->tablero);

            printf("\nBarco %d de %d | Largo: %d\n", i + 1, MAX_BARCOS, largos[i]);
            printf("Ingrese columna inicial A-J: ");
            scanf(" %c", &columnaLetra);

            printf("Ingrese fila inicial 1-10: ");
            scanf("%d", &fila);

            printf("Ingrese orientacion H/V: ");
            scanf(" %c", &orientacion);

            if(columnaLetra >= 'A' && columnaLetra <= 'J')
            {
                columna = columnaLetra - 'A';
            }
            else if(columnaLetra >= 'a' && columnaLetra <= 'j')
            {
                columna = columnaLetra - 'a';
            }
            else
            {
                columna = -1;
            }
            fila = fila - 1;

            if(puede_colocar_barco(&jugador->tablero, fila, columna, largos[i], orientacion))
            {
                  colocar_barco(&jugador->tablero, fila, columna, largos[i], orientacion);

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

                  jugador->barcos[i].posX = fila;
                  jugador->barcos[i].posY = columna;

                  jugador->barcos[i].vida = largos[i];
                  jugador->barcos[i].tamanio = largos[i];

                  jugador->barcos[i].orientacion = orientacion;

                  jugador->vidaTotal += largos[i];

                  colocado = 1;
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

void ubicar_barcos_ia(TipoJugador *ia)
{
    int largos[MAX_BARCOS] = {5, 4, 3, 3, 2};

    ia->vidaTotal = 0;

    for(int i = 0; i < MAX_BARCOS; i++)
    {
        int colocado = 0;

        while(colocado == 0)
        {
            int fila = rand() % N;
            int columna = rand() % N;
            char orientacion;

            if(rand() % 2 == 0)
                orientacion = 'H';
            else
                orientacion = 'V';

            if(puede_colocar_barco(&ia->tablero, fila, columna, largos[i], orientacion))
            {
                colocar_barco(&ia->tablero, fila, columna, largos[i], orientacion);
  
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
  
                ia->barcos[i].posX = fila;
                ia->barcos[i].posY = columna;
  
                ia->barcos[i].vida = largos[i];
                ia->barcos[i].tamanio = largos[i];
  
                ia->barcos[i].orientacion = orientacion;
  
                ia->vidaTotal += largos[i];
  
                colocado = 1;
            }
        }
    }
}

void restar_vida_barco(TipoJugador *enemigo, int fila, int columna)
{
    for(int i = 0; i < MAX_BARCOS; i++)
    {
        for(int j = 0; j < enemigo->barcos[i].tamanio; j++)
        {
            int bx = enemigo->barcos[i].posX;
            int by = enemigo->barcos[i].posY;

            if(enemigo->barcos[i].orientacion == 'H' || enemigo->barcos[i].orientacion == 'h')
                by = enemigo->barcos[i].posY + j;
            else
                bx = enemigo->barcos[i].posX + j;

            if(bx == fila && by == columna)
            {
                enemigo->barcos[i].vida--;

                if(enemigo->barcos[i].vida == 0)
                    puts("¡Barco hundido!");

                return;
            }
        }
    }
}

void disparar(TipoJugador *jugador, TipoJugador *enemigo)
{
    char letra;
    int fila;
    int columna;

    printf("\nIngrese la coordenada donde desea disparar. Ejemplo: A 5\n");
    printf("Disparo: ");
    scanf(" %c %d", &letra, &fila);

    if(letra >= 'A' && letra <= 'J')
        columna = letra - 'A';
    else if(letra >= 'a' && letra <= 'j')
        columna = letra - 'a';
    else
    {
        puts("Columna invalida.");
        return;
    }

    fila--;

    if(fila < 0 || fila >= N || columna < 0 || columna >= N)
    {
        puts("Coordenada fuera del tablero.");
        return;
    }

    if(jugador->tableroAtaques.matriz[fila][columna] == AGUA ||
       jugador->tableroAtaques.matriz[fila][columna] == IMPACTO)
    {
        puts("Ya disparaste en esa posicion.");
        return;
    }

    if(enemigo->tablero.matriz[fila][columna] == BARCO)
    {
        puts("\n*** IMPACTO ***");

        jugador->tableroAtaques.matriz[fila][columna] = IMPACTO;
        enemigo->tablero.matriz[fila][columna] = IMPACTO;

        enemigo->vidaTotal--;

        restar_vida_barco(enemigo, fila, columna);
    }
    else
    {
        puts("\nAgua.");

        jugador->tableroAtaques.matriz[fila][columna] = AGUA;

        if(enemigo->tablero.matriz[fila][columna] == LIBRE)
            enemigo->tablero.matriz[fila][columna] = AGUA;
    }

    printf("Vida restante del enemigo: %d\n", enemigo->vidaTotal);
}

void disparo_aleatorio_ia(TipoJugador *ia, TipoJugador *jugador)
{
    int fila;
    int columna;
    int disparoValido = 0;

    while(disparoValido == 0)
    {
        fila = rand() % N;
        columna = rand() % N;

        if(ia->tableroAtaques.matriz[fila][columna] == LIBRE)
        {
            disparoValido = 1;
        }
    }

    printf("\nLa IA disparo en: %c %d\n", columna + 'A', fila + 1);

    if(jugador->tablero.matriz[fila][columna] == BARCO)
    {
        puts("La IA acerto un disparo!");

        ia->tableroAtaques.matriz[fila][columna] = IMPACTO;
        jugador->tablero.matriz[fila][columna] = IMPACTO;

        jugador->vidaTotal--;

        restar_vida_barco(jugador, fila, columna);
    }
    else
    {
        puts("La IA fallo el disparo!");

        ia->tableroAtaques.matriz[fila][columna] = AGUA;

        if(jugador->tablero.matriz[fila][columna] == LIBRE)
        {
            jugador->tablero.matriz[fila][columna] = AGUA;
        }
    }
}

void ia_media(TipoJugador *ia, TipoJugador *jugador)
{
    disparo_aleatorio_ia(ia, jugador);
}
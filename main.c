#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <time.h>

//gcc funciones/*.c tarea3.c -Wno-unused-result -o main

// --- COMANDOS COMPILACION BASH ---
// gcc funciones/*.c main.c funciones.c -Werror -o main
// ./main
// ctrl + c -> forzar cierre
// 
//-----------------------------------------------
//                MAIN
//-----------------------------------------------S

// FUNCIONES
void print_title();
void iniciar_juego();
int seleccionar_dificultad();
void comenzar_partida(TipoJugador *jugador, TipoJugador *computadora, int dificultad);
void crear_mapa(Mapa *mapa);
void inicializar_jugador(TipoJugador *jugador, int id);

void print_title() 
{
    puts("=========================================================");
    puts("████   ███  █████ █████ █     █████  ████ █   █ ███ ████");
    puts("█   █ █   █   █     █   █     █     █     █   █  █  █   █");
    puts("████  █████   █     █   █     ████   ███  █████  █  ████");
    puts("█   █ █   █   █     █   █     █         █ █   █  █  █");
    puts("████  █   █   █     █   █████ █████ ████  █   █ ███ █");
    puts("=========================================================");
    puts("PRESIONA E PARA EMPEZAR");
    puts("PRESIONA I PARA INSTRUCCIONES");
    puts("PRESIONA S PARA SALIR");
    puts("");
}


void inicializar_jugador(TipoJugador *jugador, int id) 
{
    jugador->id = id;
    jugador->vidaTotal = 0;
    jugador->historial = NULL;

    crear_mapa(&jugador->tablero);
    crear_mapa(&jugador->tableroAtaques);
}

void crear_mapa(Mapa *mapa)
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            mapa->matriz[i][j]=0;
        }
    }
}


void iniciar_juego() 
{
    TipoJugador jugador;
    TipoJugador computadora;

    int dificultad;

    inicializar_jugador(&jugador,1);
    inicializar_jugador(&computadora,2);

    dificultad = seleccionar_dificultad();

    system("clear");
    puts("=================================");
    puts("      UBICACION DE BARCOSS");
    puts("=================================");

    
    ubicar_barcos_jugador(&jugador);
    

    puts("\nTodos los barcos fueron ubicados.");
    puts("Presione ENTER para continuar...");
    getchar();
    getchar();

    system("clear");
    puts("La computadora esta ubicando sus barcos...");

    ubicar_barcos_ia(&computadora);

    puts("Barcos enemigos posicionados.");
    puts("Presione ENTER para continuar...");
    getchar();

    comenzar_partida(&jugador, &computadora, dificultad);
}

int seleccionar_dificultad() {
    int dificultad;

    do 
    {
        system("clear");

        puts("=================================");
        puts("      SELECCIONAR DIFICULTAD");
        puts("=================================");
        puts("1. Facil");
        puts("2. Media");
        puts("3. Dificil");
        puts("=================================");
        printf("Seleccione una opcion: ");

        scanf("%d", &dificultad);

        if(dificultad < 1 || dificultad > 3) 
        {
            puts("Opcion invalida.");
            puts("Presione ENTER para intentar nuevamente...");
            getchar();
            getchar();
        }

    } while(dificultad < 1 || dificultad > 3);

    return dificultad;
}

void turno_ia(TipoJugador *ia, TipoJugador *jugador, int dificultad)
{
    if(dificultad == 1) 
    {
        ia_media(ia, jugador);
    }
    else if(dificultad == 2) 
    {
        ia_media(ia, jugador);
    }
    else if(dificultad == 3) 
    {
        puts("IA Dificil: modo cazador.");
           //ia_dificil();
    }
}


void mostrar_tableros_partida(Mapa tableroEnemigo, Mapa tableroPersonal) 
{
    puts("=========================================================");
    puts("==================== TURNO: JUGADOR ====================");
    puts("=========================================================");
    puts("        TABLERO ENEMIGO              TABLERO PERSONAL");
    puts("    A B C D E F G H I J          A B C D E F G H I J");

    for(int i = 0; i < N; i++) 
    {
        printf("%2d  ", i + 1);

        for(int j = 0; j < N; j++) 
        {
            if(tableroEnemigo.matriz[i][j] == AGUA) 
            {
                printf("* ");
            }
            else if(tableroEnemigo.matriz[i][j] == IMPACTO) 
            {
                printf("X ");
            }
            else 
            {
                printf("- ");
            }
        }

        printf("     %2d  ", i + 1);

        for(int j = 0; j < N; j++) {
            if(tableroPersonal.matriz[i][j] == BARCO) 
            {
                printf("B ");
            }
            else if(tableroPersonal.matriz[i][j] == AGUA) 
            {
                printf("* ");
            }
            else if(tableroPersonal.matriz[i][j] == IMPACTO)
            {
                printf("X ");
            }
            else 
            {
                printf("- ");
            }
        }

        printf("\n");
    }

    puts("==========================================================");
}


void comenzar_partida(TipoJugador *jugador, TipoJugador *computadora, int dificultad) {
    int opcion;
    int partidaTerminada = 0;

    while(partidaTerminada != 1) 
    {
        system("clear");

        mostrar_tableros_partida(jugador->tableroAtaques, jugador->tablero);
        
        puts("=================================");
        puts("     6     BATTLESHIPS");
        puts("=================================");
        puts("0. Salir al menu principal");
        puts("1. Disparar");

        if(dificultad == 1) {
            puts("2. Deshacer movimiento");
        }

        puts("=================================");
        printf("Seleccione una opcion: ");

        char entrada[10];

        printf("Seleccione una opcion: ");
        scanf(" %9s", entrada);

        if(entrada[0] < '0' || entrada[0] > '9')
        {
            puts("\nOpcion invalida. Debe ingresar un numero.");
            puts("Presione ENTER para continuar...");
            getchar();
            getchar();
            continue;
        }

        opcion = entrada[0] - '0';

        switch(opcion) {
            case 0:
                puts("\nSaliendo de la partida.");
                partidaTerminada = 1;
                break;

            case 1:
                disparar(jugador, computadora);

                if(computadora->vidaTotal <= 0)
                {
                    puts("\n¡Ganaste la partida!");
                    partidaTerminada = 1;
                }
                else
                {
                    puts("\nTURNO IA");
                    turno_ia(computadora, jugador, dificultad);
                }
                break;

            case 2:
                if(dificultad == 1) {
                    puts("\n[DESHACER MOVIMIENTO]");

                    //   deshacer_movimiento();

                } else {
                    puts("\nOpcion invalida.");
                }
                break;

            default:
                puts("\nOpcion invalida.");
                break;
        }

        if(!partidaTerminada) {
            puts("\nPresione ENTER para continuar...");
            getchar();
            getchar();
        }
    }
}



int main() {
    char option;
    srand(time(NULL));
    
    do {
        print_title();
        scanf(" %c", &option);

        switch(option) {
            case 'E':
            case 'e':
                system("clear");
                iniciar_juego();
                break;

            case 'I':
            case 'i':
                system("clear");
                puts("=========== INSTRUCCIONES ===========");
                puts("1. Selecciona una dificultad.");
                puts("2. Ubica tus barcos.");
                puts("3. Destruye todos los barcos enemigos.");
                puts("4. Puedes salir de la partida desde el menu de juego.");
                puts("=====================================");
                break;

            case 'S':
            case 's':
                puts("Saliendo del juego...");
                break;

            default:
                puts("Opcion invalida.");
                break;
        }

        if(option != 'S' && option != 's') {
            puts("\nPresione ENTER para continuar...");
            getchar();
            getchar();
            system("clear");
        }

    } while(option != 'S' && option != 's');

    return 0;
}


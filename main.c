#include "include/funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include "include/list.h"
#include <time.h>
#include "include/des_turno.h"

// --- COMANDOS COMPILACION BASH ---
// gcc include/*.c main.c -Werror -o main
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

// Inicio del juego, es lo primero que se ve al inciiar el juego.
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


// inicializa la estructura de un jugador al comenzar la partida
void inicializar_jugador(TipoJugador *jugador, int id) 
{
    jugador->id = id; // asigna el id
    jugador->vidaTotal = 0; // asigna la vida total

    crear_mapa(&jugador->tablero); // iniciaiza la vida total del jugad
    crear_mapa(&jugador->tableroAtaques); // inicializa el tablero donde se registran los ataques realizados
}

// inicializa tablero de juego, el cual es una matriz
void crear_mapa(Mapa *mapa)
{
    for(int i=0;i<N;i++) // recorre las filas
    {
        for(int j=0;j<N;j++) // recorre las columnas de la fila actual
        {
            mapa->matriz[i][j]=0; // incializa  la casilla como libre
        }
    }
}

// incializa una nueva partida del juego
void iniciar_juego() 
{
    // estrusturas del jugador y la computadora IA
    TipoJugador jugador;
    TipoJugador computadora;

    int dificultad;

    // inicializa los jugadores jugador y computadora y sus tableros
    inicializar_jugador(&jugador,1);
    inicializar_jugador(&computadora,2);

    // selecciona la dificultad de la partida
    dificultad = seleccionar_dificultad();

    system("clear");
    puts("=================================");
    puts("      UBICACION DE BARCOS");
    puts("=================================");

    // el jugador ubica sus barcos
    ubicar_barcos_jugador(&jugador);
    

    puts("\nTodos los barcos fueron ubicados.");
    puts("Presione ENTER para continuar...");
    getchar();
    getchar();

    system("clear");
    puts("La computadora esta ubicando sus barcos...");

    // la ia ubica sus barcos
    ubicar_barcos_ia(&computadora);

    puts("Barcos enemigos posicionados.");
    puts("Presione ENTER para continuar...");
    getchar();

    // comienza la partida
    comenzar_partida(&jugador, &computadora, dificultad);
}

// funcion que permite al jugadro seleccionar la difucultad de la partida
int seleccionar_dificultad() {
    int dificultad;

    do // se repite el ciclo hasta qyue se ingrese una dificultad valida
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

        scanf("%d", &dificultad); // lee la dificultad

        if(dificultad < 1 || dificultad > 3) // verifica que sea una opcion valida
        {
            puts("Opcion invalida.");
            puts("Presione ENTER para intentar nuevamente...");
            getchar();
            getchar();
        }

    } while(dificultad < 1 || dificultad > 3);

    return dificultad; // retorna la dificultad
}

// funcion que ejecuta el turno de la ia segun la dificultad que se selecciona
void turno_ia(TipoJugador *ia, TipoJugador *jugador, int dificultad)
{
    if(dificultad == 1)  // IA faci
    {
        ia_media(ia, jugador);
    }
    else if(dificultad == 2) // ia media
    {
        ia_media(ia, jugador);
    }
    else if(dificultad == 3) // ia dificil modo cazador y captura
    {
        puts("IA Dificil: modo cazador.");
           ia_dificil(ia, jugador);
    }
}

// funcionm que muestra los taberos del jugador y del enemigo durante la partida
void mostrar_tableros_partida(Mapa tableroEnemigo, Mapa tableroPersonal) 
{
    // encabezado de los taberos
    puts("=========================================================");
    puts("=================== TABLERO DE JUEGO ====================");
    puts("=========================================================");
    puts("        TABLERO ENEMIGO              TABLERO PERSONAL");
    puts("    A B C D E F G H I J          A B C D E F G H I J");

    for(int i = 0; i < N; i++) // recorre todas las filas del tablero
    {
        printf("%2d  ", i + 1);

        // muestra el tabnlero de ataques del jugador
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

        // muesta el tablero personal del jugador
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

// funcion que controla el ciclo principal del juego
void comenzar_partida(TipoJugador *jugador, TipoJugador *computadora, int dificultad) {
    int opcion;
    int partidaTerminada = 0;
    List * pila_movimiento = NULL;
    pila_movimiento = list_create();

    while(partidaTerminada != 1) // while principal de la partida
    {
        system("clear");

        mostrar_tableros_partida(jugador->tableroAtaques, jugador->tablero); // muestra los tableros
        
        puts("==========================================================");
        puts("                       BATTLESHIPS");
        puts("==========================================================");
        puts("0. Salir al menu principal");
        puts("1. Disparar");

        if(dificultad == 1) {
            puts("2. Deshacer movimiento");
        }

        puts("==========================================================");
        char entrada[10];

        // solicita al jugador una opcion
        printf("Seleccione una opcion: ");
        scanf(" %9s", entrada);

        if(entrada[0] < '0' || entrada[0] > '9') // verifica si la opcion es valida
        {
            puts("\nOpcion invalida. Debe ingresar un numero.");
            puts("Presione ENTER para continuar...");
            getchar();
            getchar();
            continue;
        }

        opcion = entrada[0] - '0';

        switch(opcion) { // opciones de juego
            case 0: // finalizar el juego
                puts("\nSaliendo de la partida.");
                partidaTerminada = 1;
                break;

            case 1: // turno del jugador
                if(dificultad == 1) { // em modo facil se activa el guardar turno
                    guardar_turno(pila_movimiento, jugador, computadora);
                }

                disparar(jugador, computadora); // realiza un disparo el jugador

                if(computadora->vidaTotal <= 0) // verifica si el jugador gana
                {
                    puts("\n¡Ganaste la partida!");
                    partidaTerminada = 1;
                }
                else // turno de la IA
                {
                    puts("\n==========================================================");
                    printf("               ========= TURNO IA =========\n");
                    puts("==========================================================");
                    turno_ia(computadora, jugador, dificultad);
                }
                break;

            case 2: // Deshace el ultimo movimiento, opcion disponible solo en el modo facil
                if(dificultad == 1) {
                    puts("\n[DESHACER MOVIMIENTO]");

                    deshacer_movimiento(pila_movimiento, jugador,  computadora);

                } else {
                    puts("\nOpcion invalida.");
                }
                break;

            default: // manejo de opciones no validas
                puts("\nOpcion invalida.");
                break;
        }

        if(!partidaTerminada) { // espera antes de actualizar la pantalla
            puts("\nPresione ENTER para continuar...");
            getchar();
            getchar();
        }
    }
    // libera la memoria utilizada por el historial
    if (pila_movimiento != NULL) {
        // Asumiendo que list_clean vacía los nodos y free destruye el puntero de la lista
        list_clean(pila_movimiento); 
        free(pila_movimiento);
    }
}


// main del juego
int main() {
    char option;
    srand(time(NULL)); // inicializa generar posiciones aleatorias de la ia
    
    do { // muestra el menu principal hasta que el usuario decida salir
        print_title();
        scanf(" %c", &option); // opcion que selecciona el jugador

        switch(option) {
            case 'E': // inicia una nueva partida
            case 'e':
                system("clear");
                iniciar_juego();
                break;

            case 'I': // instrucciones del juego
            case 'i':
                system("clear");
                puts("=========== INSTRUCCIONES ===========");
                puts("1. Selecciona una dificultad.");
                puts("2. Ubica tus barcos.");
                puts("3. Destruye todos los barcos enemigos.");
                puts("4. Puedes salir de la partida desde el menu de juego.");
                puts("=====================================");
                break;

            case 'S': // salir del juego
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

    } while(option != 'S' && option != 's'); // se acaba cuando encuentre una s

    return 0;
}


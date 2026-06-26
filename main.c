#include "include/funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include "include/list.h"
#include <time.h>
#include "include/des_turno.h"

// --- COMANDOS COMPILACIÓN BASH ---
// gcc include/*.c main.c -Werror -o main
// ./main
// ctrl + c -> Forzar 
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

// Inicio del juego, es lo primero que se ve al iniciar el juego.
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


// Inicializa la estructura de un jugador al comenzar la partida
void inicializar_jugador(TipoJugador *jugador, int id) 
{
    jugador->id = id; // asigna el id
    jugador->vidaTotal = 0; // asigna la vida total

    crear_mapa(&jugador->tablero); // Inicializa la vida total del jugador
    crear_mapa(&jugador->tableroAtaques); // Inicializa el tablero donde se registran los ataques realizados
}

// Inicializa tablero de juego, el cual es una matriz
void crear_mapa(Mapa *mapa)
{
    for(int i=0;i<N;i++) // Recorre las filas
    {
        for(int j=0;j<N;j++) // Recorre las columnas de la fila 
        {
            mapa->matriz[i][j]=0; // Inicializa la casilla como libre
        }
    }
}

// Inicializa una nueva partida del juego
void iniciar_juego() 
{
    // Estructuras del jugador y la computadora IA
    TipoJugador jugador;
    TipoJugador computadora;

    int dificultad;

    // Inicializa los jugadores jugador y computadora y sus tableros
    inicializar_jugador(&jugador,1);
    inicializar_jugador(&computadora,2);

    // Selecciona la dificultad de la partida
    dificultad = seleccionar_dificultad();

    system("clear");
    puts("=================================");
    puts("      UBICACION DE BARCOS");
    puts("=================================");

    // El jugador ubica sus barcos
    ubicar_barcos_jugador(&jugador);
    

    puts("\nTodos los barcos fueron ubicados.");
    puts("Presione ENTER para continuar...");
    getchar();
    getchar();

    system("clear");
    puts("La computadora esta ubicando sus barcos...");

    // La IA ubica sus barcos
    ubicar_barcos_ia(&computadora);

    puts("Barcos enemigos posicionados.");
    puts("Presione ENTER para continuar...");
    getchar();

    // Comienza la partida
    comenzar_partida(&jugador, &computadora, dificultad);
}

// Función que permite al jugador seleccionar la dificultad de la partida
int seleccionar_dificultad() {
    int dificultad;

    do // Se repite el ciclo hasta que se ingrese una dificultad válida
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

        if(dificultad < 1 || dificultad > 3) // Verifica que sea una opción válida
        {
            puts("Opcion invalida.");
            puts("Presione ENTER para intentar nuevamente...");
            getchar();
            getchar();
        }

    } while(dificultad < 1 || dificultad > 3);

    return dificultad; // Retorna la dificultad
}

// Función que ejecuta el turno de la IA según la dificultad que se selecciona
void turno_ia(TipoJugador *ia, TipoJugador *jugador, int dificultad)
{
    if(dificultad == 1)  // IA fácil
    {
        ia_media(ia, jugador);
    }
    else if(dificultad == 2) // IA media
    {
        ia_media(ia, jugador);
    }
    else if(dificultad == 3) // IA difícil modo cazador y captura
    {
        puts("IA Dificil: modo cazador.");
           ia_dificil(ia, jugador);
    }
}

// Función que muestra los tableros del jugador y del enemigo durante la partida
void mostrar_tableros_partida(Mapa tableroEnemigo, Mapa tableroPersonal) 
{
    // Encabezado de los tableros
    puts("=========================================================");
    puts("=================== TABLERO DE JUEGO ====================");
    puts("=========================================================");
    puts("        TABLERO ENEMIGO              TABLERO PERSONAL");
    puts("    A B C D E F G H I J          A B C D E F G H I J");

    for(int i = 0; i < N; i++) // Recorre todas las filas del tablero
    {
        printf("%2d  ", i + 1);

        // Muestra el tablero de ataques del jugador
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

        // Muestra el tablero personal del jugador
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

// Función que controla el ciclo principal del juego
void comenzar_partida(TipoJugador *jugador, TipoJugador *computadora, int dificultad) {
    int opcion;
    int partidaTerminada = 0;
    List * pila_movimiento = NULL;
    pila_movimiento = list_create();

    while(partidaTerminada != 1) // while principal de la partida
    {
        system("clear");

        mostrar_tableros_partida(jugador->tableroAtaques, jugador->tablero); // Muestra los tableros
        
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

        // Solicita al jugador una opción
        printf("Seleccione una opcion: ");
        scanf(" %9s", entrada);

        if(entrada[0] < '0' || entrada[0] > '9') // Verifica si la opción es válida
        {
            puts("\nOpcion invalida. Debe ingresar un numero.");
            puts("Presione ENTER para continuar...");
            getchar();
            getchar();
            continue;
        }

        opcion = entrada[0] - '0';

        switch(opcion) { // Opciones de juego
            case 0: // finalizar el juego
                puts("\nSaliendo de la partida.");
                partidaTerminada = 1;
                break;

            case 1: // Turno del jugador
                if(dificultad == 1) { // em modo facil se activa el guardar turno
                    guardar_turno(pila_movimiento, jugador, computadora);
                }

                disparar(jugador, computadora); // Realiza un disparo el jugador

                if(computadora->vidaTotal <= 0) // Verifica si el jugador gana
                {
                    puts("\n¡Ganaste la partida!");
                    partidaTerminada = 1;
                }
                else // Turno de la IA
                {
                    puts("\n==========================================================");
                    printf("               ========= TURNO IA =========\n");
                    puts("==========================================================");
                    turno_ia(computadora, jugador, dificultad);
                }
                break;

            case 2: // Deshace el último movimiento, opción disponible solo en el modo fácil
                if(dificultad == 1) {
                    puts("\n[DESHACER MOVIMIENTO]");

                    deshacer_movimiento(pila_movimiento, jugador,  computadora);

                } else {
                    puts("\nOpcion invalida.");
                }
                break;

            default: // Manejo de opciones no válidas
                puts("\nOpcion invalida.");
                break;
        }

        if(!partidaTerminada) { // Espera antes de actualizar la pantalla
            puts("\nPresione ENTER para continuar...");
            getchar();
            getchar();
        }
    }
    // Libera la memoria utilizada por el historial
    if (pila_movimiento != NULL) {
        // Asumiendo que list_clean vacía los nodos y free destruye el puntero de la lista
        list_clean(pila_movimiento); 
        free(pila_movimiento);
    }
}


// main del juego
int main() {
    char option;
    srand(time(NULL)); // Inicializa generar posiciones aleatorias de la IA
    
    do { // Muestra el menú principal hasta que el usuario decida salir
        print_title();
        scanf(" %c", &option); // Opción que selecciona el jugador

        switch(option) {
            case 'E': // Inicia una nueva partida
            case 'e':
                system("clear");
                iniciar_juego();
                break;

            case 'I': // Instrucciones del juego
            case 'i':
                system("clear");
                puts("=========== INSTRUCCIONES ===========");
                puts("1. Selecciona una dificultad.");
                puts("2. Ubica tus barcos.");
                puts("3. Destruye todos los barcos enemigos.");
                puts("4. Puedes salir de la partida desde el menu de juego.");
                puts("=====================================");
                break;

            case 'S': // Salir del juego
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


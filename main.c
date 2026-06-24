
#include <stdio.h>
#include <stdlib.h>
#include "list.h"


#define N 10
#define MAX_BARCOS 5

typedef struct Node {
    int x;
    int y;
    int resultado;
    struct Node *next;
} Node;

typedef Node* pila;

typedef struct{
    int matriz[N][N];
} Mapa;

typedef struct{
    int ancho;
    int largo;
    int posX;
    int posY;
    int vida;
} TipoBarco;

typedef struct{
    int x;
    int y;
    int resultado;
} Accion;

typedef struct{
    int id;
    Mapa tablero;
    TipoBarco barcos[MAX_BARCOS];
    int vidaTotal;
    List *historial;
} TipoJugador;

// --- COMANDOS COMPILACION BASH ---
// gcc main.c -Werror -o main
// ./main
// ctrl + c -> forzar cierre
// 
//-----------------------------------------------
//                MAIN
//-----------------------------------------------

// FUNCIONES
void print_title();
void iniciar_juego();
int seleccionar_dificultad();
void comenzar_partida(int dificultad);


void print_title() {
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

void iniciar_juego() {
    int dificultad;

    dificultad = seleccionar_dificultad();

    system("clear");
    puts("=================================");
    puts("      UBICACION DE BARCOSS");
    puts("=================================");

    
       //posicionar_barcos();
    

    puts("\nTodos los barcos fueron ubicados.");
    puts("Presione ENTER para continuar...");
    getchar();
    getchar();

    system("clear");
    puts("La computadora esta ubicando sus barcos...");

      // posicionar_barcos_bot();

    puts("Barcos enemigos posicionados.");
    puts("Presione ENTER para continuar...");
    getchar();

    comenzar_partida(dificultad);
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

void turno_ia(int dificultad) 
{

    if(dificultad == 1) 
    {
        puts("IA Facil");
        
        // ia_facil();
    }
    else if(dificultad == 2) 
    {
        puts("IA Media");
          // ia_media();
    }
    else if(dificultad == 3) 
    {
        puts("IA Dificil: modo cazador.");
           //ia_dificil();
    }
}

void comenzar_partida(int dificultad) {
    int opcion;
    int partidaTerminada = 0;

    while(partidaTerminada != 1) 
    {
        system("clear");

        puts("=================================");
        puts("     6     BATTLESHIPS");
        puts("=================================");
        puts("0. Salir al menu principal");
        puts("1. Disparar");
        puts("2. Mostrar tablero propio");
        puts("3. Mostrar tablero de ataques");

        if(dificultad == 1) {
            puts("4. Deshacer movimiento");
        }

        puts("=================================");
        printf("Seleccione una opcion: ");

        scanf("%d", &opcion);

        switch(opcion) {
            case 0:
                puts("\nSaliendo de la partida.");
                partidaTerminada = 1;
                break;

            case 1:
                puts("\n[DISPARAR]");

                  // disparar();
                puts("\nTURNO IA");
                turno_ia(dificultad);
                break;

            case 2:
                puts("\n[MOSTRAR TABLERO PROPIO]");
                
                  // mostrar_tablero();
                
                break;

            case 3:
                puts("\n[MOSTRAR TABLERO DE ATAQUES]");

                //   mostrar_tablero_ataques();

                break;

            case 4:
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


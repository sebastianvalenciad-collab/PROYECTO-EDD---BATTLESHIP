
#include <stdio.h>
#include <stdlib.h>

// --- COMANDOS COMPILACION BASH ---
// gcc main.c -Werror -o main
// ./main
// ctrl + c -> forzar cierre

//-----------------------------------------------
//                MAIN
//-----------------------------------------------

void print_title () {
    puts("=========================================================");
    puts("████   ███  █████ █████ █     █████  ████ █   █ ███ ████");
    puts("█   █ █   █   █     █   █     █     █     █   █  █  █   █");
    puts("████  █████   █     █   █     ████   ███  █████  █  ████");
    puts("█   █ █   █   █     █   █     █         █ █   █  █  █");
    puts("████  █   █   █     █   █████ █████ ████  █   █ ███ █");
    puts("=========================================================");
    puts("PRESIONA E PARA EMPEZAR ");
    puts("(PRESIONA I PARA INSTRUCCIONES / S PARA SALIR)");
    puts("");
}

int main(){

    char option;
    do {
        print_title();
        option = getchar();

        switch (option) {
        case 'E': //TODO -> ENCONTRRAR FORMA DE QUE C 
                  // leea la tecla enter (no pude con '\n')
            system("clear");
            puts("EMPEZAR______");
            break;
        case 'I':
            system("clear");
            puts("INSTRUCCIONES");
            break;
        }

        if (option != 'S'){
            puts("Presione una tecla para continuar...");
            getchar(); // Consume el '\n' del buffer de entrada
            getchar(); // Espera a que el usuario presione una tecla
            system("clear");
        }

    } while (option != 'S');

    
    return 0;
}
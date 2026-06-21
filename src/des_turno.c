#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct {
    TipoJugador JUGADOR_TURNO_ACTUAL;
    TipoJugador ENEMIGO_TURNO_ACTUAL;
} TipoTurno;

typedef enum {
    ERR_OK = 0,
    // Errores Comunes de Punteros
    ERR_PUNTERO_NULO,
    ERR_SIN_MEMORIA,
    
    // Errores específicos de la Pila (Stack)
    ERR_PILA_VACIA,       // Intentar hacer POP o TOP en una pila sin elementos
    ERR_PILA_LLENA,       // Intentar hacer PUSH en una pila con tamaño fijo que se llenó
    
    // Errores específicos de la Matriz
    ERR_INDICE_INVALIDO,  // Intentar acceder a una fila o columna que no existe
    ERR_MATRIZ_INVALIDA   // Dimensiones menores o iguales a cero (ej. 0x0)
} Status;

void manejar_error (Status estado, const char *contexto){
    if (estado == ERR_OK) return;
    // Si todo está bien, no hacemos nada
    fprintf(stderr, "[ERROR] En '%s': ", contexto);

    // Imprimimos el contexto y el error detallado en stderr (salida de errores)
    switch (estado) {
        case ERR_PUNTERO_NULO:
            fprintf(stderr, "El puntero recibido apunta a NULL (Estructura no inicializada).\n");
            break;
        case ERR_SIN_MEMORIA:
            fprintf(stderr, "No hay suficiente memoria RAM disponible (malloc fallo).\n");
            break;
        case ERR_PILA_VACIA:
            fprintf(stderr, "No se pueden extraer elementos. La pila esta vacia (Underflow).\n");
            break;
        case ERR_PILA_LLENA:
            fprintf(stderr, "No se pueden agregar elementos. La pila esta al maximo (Overflow).\n");
            break;
        case ERR_INDICE_INVALIDO:
            fprintf(stderr, "Fila o columna fuera de los limites de la matriz.\n");
            break;
        case ERR_MATRIZ_INVALIDA:
            fprintf(stderr, "Las dimensiones de la matriz deben ser mayores a cero.\n");
            break;
        default:
            fprintf(stderr, "Error desconocido.\n");
            break;
    }
    // Opcional: Si el error es crítico, puedes abortar el programa aquí
    // exit(estado);
}

// ------------------------------------------------------------------------

// --- Algoritmo deshacer movimiento ---
// Antes de terminar el turno, se le da la opcion al jugador de 
// revertir a un turno anterior en caso contrario, el juego sigue
// con el siguiente turno.


/*
## Función void 'guardar_turno' 
// Insertar al final de un turno del loop de juego (modo fácil)

**ENTRADA**
PILA movimientos, TipoJugador *JUGADOR, TipoJugador *ENEMIGO`
**PROCESO**
1. Verificar existencia de JUGADOR, ENEMIGO y movimientos
// Tipo turno contiene la información variable de los dos jugadores
2. Capturar el estado actual: Crear nuevo nodo TipoTurno y reservar memoria 
3. Verificar integridad del nodo
4. Apilar en PILA movimientos

*/


void guardar_turno (List * movimientos, const TipoJugador * JUGADOR, const TipoJugador *ENEMIGO){
    // Veridicar la existencia de los datos y la Pila
    if (!movimientos || !JUGADOR || !ENEMIGO) {
        manejar_error(ERR_PUNTERO_NULO, "guardar_turno verificacion inicial fallida.");
        return;
    }
    // Reserva de momoria para el nodo en el heap
    TipoTurno * nuevo_turno = (TipoTurno *) malloc(sizeof(TipoTurno));
    
    if (nuevo_turno == NULL) {
        manejar_error(ERR_SIN_MEMORIA, "guardar_turno al crear nodo");
        return;
    }
    // Asignacion / copia del turno actual en el nodo
    nuevo_turno->JUGADOR_TURNO_ACTUAL = JUGADOR;
    nuevo_turno->ENEMIGO_TURNO_ACTUAL = ENEMIGO;
    // Apilar puntero en la Pila / lista movimientos
    list_pushBack(movimientos, &nuevo_turno); 
}


/*
## Función void'deshacer_movimiento' 
// Llamar si el jugador decide deshacer un turno al final del turno actual

**ENTRADA**
PILA movimientos 
**PROCESO**
1. Verificar que existan turno(s) anterior (Pila no vacía)
	   1.1 Imprimir "NO EXIXSTEN TURNOS PREVIOS BUCANERO" en caso de pila vacia
2. Verificar integridad del nodo.
3. Desapilar top PILA movimientos.
4. Llamar a función 'remplazar_datos'(Cambia los datos actuales por los del nodo)
5. Liberar el nodo desapilado
6. Iniciar siguiente turno para que se reimpriman los datos
// Creo que es mejor esto a que el jugador decida el mismo la cantidad de turnos a devolverse, ya que asi se puede revisar de forma visual cada turno.
*/

void deshacer_movimiento (List * movimientos, TipoJugador * JUGADOR, TipoJugador *ENEMIGO){
    
    // --- VERIFICACION DE DATOS ---
    // Verificar integridad de la pila / lista
    if(!movimientos) {
        manejar_error(ERR_PUNTERO_NULO, "deshacer_movimiento verificacion inicial de PILA fallida.");
        return;
    }
    
    // Verificar que existan turnos
    if (list_size(movimientos) == 0) {
        puts("NO EXISTEN TURNOS PREVIOS BUCANERO")
        return;
    }
    // --- RECUPERACION TURNO ANTERIOR ---    
    // Desapilar ultimo turno
    TipoTurno * turno_anterior = list_popBack(movimientos);
    
    // verificar integridad del nodo
    if (!turno_anterior) {
        manejar_error(ERR_PUNTERO_NULO, "deshacer_movimiento nodo de TOP invalido.");
        return;
    }

    // Se remplazan los datos 
    remplazar_datos(turno_anterior, JUGADOR, ENEMIGO);

    // Liberar nodo:  Segun yo, pop libera la memoria del nodo, creo....
        
    
    
}
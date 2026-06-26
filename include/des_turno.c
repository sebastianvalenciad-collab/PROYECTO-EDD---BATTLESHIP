
#include "des_turno.h"

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


void guardar_turno (List * movimientos, TipoJugador * JUGADOR, TipoJugador *ENEMIGO){
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
    // Se agrega el '*' para desreferenciar los punteros y copiar el valor
    nuevo_turno->JUGADOR_TURNO_ACTUAL = *JUGADOR;
    nuevo_turno->ENEMIGO_TURNO_ACTUAL = *ENEMIGO;
    // Apilar puntero en la Pila / lista movimientos
    list_pushBack(movimientos, nuevo_turno); 
    
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

void remplazar_datos (TipoTurno * turno_anterior, TipoJugador * JUGADOR, TipoJugador *ENEMIGO) {
    // Desreferenciar para modificar la estructura original y usar la variable del turnno anterior
    *JUGADOR = turno_anterior->JUGADOR_TURNO_ACTUAL;
    *ENEMIGO = turno_anterior->ENEMIGO_TURNO_ACTUAL;
}

void deshacer_movimiento (List * movimientos, TipoJugador * JUGADOR, TipoJugador *ENEMIGO){
    
    // --- VERIFICACION DE DATOS ---
    // Verificar integridad de la pila / lista
    if(!movimientos || !JUGADOR || !ENEMIGO) {
        manejar_error(ERR_PUNTERO_NULO, "deshacer_movimiento verificacion inicial de PILA fallida.");
        return;
    }
    
    // Verificar que existan turnos
    if (list_size(movimientos) == 0) {
        puts("NO EXISTEN TURNOS PREVIOS BUCANERO");
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
    // update: se libera el dato del nodo, pero no el tipo
    free(turno_anterior);
    
    
}
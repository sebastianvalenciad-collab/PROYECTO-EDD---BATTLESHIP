#ifndef DES_TURNO_H
#define DES_TURNO_H

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "manejo_errores.h"

typedef struct {
    int id;
    Mapa tablero;
    Mapa tableroAtaques;
    TipoBarco barcos[MAX_BARCOS];
    int vidaTotal;
    pila historial;
} TipoJugador;

typedef struct {
    TipoJugador JUGADOR_TURNO_ACTUAL;
    TipoJugador ENEMIGO_TURNO_ACTUAL;
} TipoTurno;

// ------------------------------------------------------------------------

// --- Algoritmo deshacer movimiento ---
// Antes de terminar el turno, se le da la opcion al jugador de 
// revertir a un turno anterior en caso contrario, el juego sigue
// con el siguiente turno.
 
// AL final del turno, se le pregunta al jugador
// si quiere reverir al turno anteriror (solo modo facil), si es positivo,
// se revierte al inicio del turno anterior, en caso contrario, se guarda el turno 
// actual y se sigue con el siguiente turno.

// ¡IMPORTANTE! SE ASUME QUE LA ESTRUCTURA TIPO JUGADOR SOLO CONTIENE 
// DATOS PRIMITIVOS (se realiza una copia superficial en vez de una copia profunda)
// asi no pasan cosas como memory leaks y se puede asignar de forma directa con la
// estructura Tipo turno.

void guardar_turno (List * movimientos, const TipoJugador * JUGADOR, const TipoJugador *ENEMIGO);

void remplazar_datos (TipoTurno * turno_anterior, TipoJugador * JUGADOR, TipoJugador *ENEMIGO);

void deshacer_movimiento (List * movimientos, TipoJugador * JUGADOR, TipoJugador *ENEMIGO);

#endif
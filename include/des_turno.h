#ifndef DES_TURNO_H
#define DES_TURNO_H

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "manejo_errores.h"
#include "funciones.h"

typedef struct {
    TipoJugador JUGADOR_TURNO_ACTUAL;
    TipoJugador ENEMIGO_TURNO_ACTUAL;
} TipoTurno;

// ------------------------------------------------------------------------

// --- Algoritmo deshacer movimiento ---
// Justo antes de disparar, el juego guarda el turno 
// si el jugador elijio el modo facil.
// (si dejas guardar_turno al final del bucle, vas a guardar turnos repetidos si
// el jugador presiona una opción inválida, o peor, vas a guardar el turno después 
// de haber deshecho un movimiento.)
 
// AL final del turno, se le pregunta al jugador
// si quiere reverir al turno anteriror (solo modo facil), si es positivo,
// se revierte al inicio del turno anterior, en caso contrario, se sigue la partida.

// ¡IMPORTANTE! SE ASUME QUE LA ESTRUCTURA TIPO JUGADOR SOLO CONTIENE 
// DATOS PRIMITIVOS (se realiza una copia superficial en vez de una copia profunda)
// asi no pasan cosas como memory leaks y se puede asignar de forma directa con la
// estructura Tipo turno.

void guardar_turno (List * movimientos, TipoJugador * JUGADOR, TipoJugador *ENEMIGO);

void remplazar_datos (TipoTurno * turno_anterior, TipoJugador * JUGADOR, TipoJugador *ENEMIGO);

void deshacer_movimiento (List * movimientos, TipoJugador * JUGADOR, TipoJugador *ENEMIGO);

#endif
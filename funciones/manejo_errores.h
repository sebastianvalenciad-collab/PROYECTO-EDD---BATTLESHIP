#ifndef MANEJO_ERRORES_H
#define MANEJO_ERRORES_H

#include <stdio.h>
#include <stdlib.h>

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

void manejar_error (Status estado, const char *contexto);

#endif
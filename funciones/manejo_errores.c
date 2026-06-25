
#include "manejo_errores.h"

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
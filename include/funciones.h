#ifndef FUNCIONES_H
#define FUNCIONES_H

#define N 10
#define MAX_BARCOS 5

#define LIBRE 0
#define BARCO 1
#define AGUA 2
#define IMPACTO 3

typedef struct Node {
    int x;
    int y;
    int resultado;
    struct Node *next;
} Node;

typedef Node* pila;

typedef struct {
    int matriz[N][N];
} Mapa;

typedef struct {
    int ancho;
    int largo;
    int posX;
    int posY;
    int vida;
    int tamanio;
    char orientacion;
} TipoBarco;

typedef struct {
    int x;
    int y;
    int resultado;
} Accion;

typedef struct {
    int id;
    Mapa tablero;
    Mapa tableroAtaques;
    TipoBarco barcos[MAX_BARCOS];
    int vidaTotal;
} TipoJugador;

void crear_mapa(Mapa *mapa);
void inicializar_jugador(TipoJugador *jugador, int id);
void turno_ia(TipoJugador *ia, TipoJugador *jugador, int dificultad);
int posicion_valida(int x, int y);
int puede_colocar_barco(Mapa *mapa, int x, int y, int largo, char orientacion);
void colocar_barco(Mapa *mapa, int x, int y, int largo, char orientacion);
void ubicar_barcos_jugador(TipoJugador *jugador);
void ubicar_barcos_ia(TipoJugador *ia);
void mostrar_mapa(Mapa mapa);
void disparar(TipoJugador *jugador, TipoJugador *enemigo);
void restar_vida_barco(TipoJugador *enemigo, int fila, int columna);
void ia_media(TipoJugador *ia, TipoJugador *jugador);
void disparo_aleatorio_ia(TipoJugador *ia, TipoJugador *jugador);

void ia_dificil(TipoJugador *ia, TipoJugador *jugador);
void agregar_vecinos_ia(int fila, int columna, TipoJugador *ia);
void turno_ia(TipoJugador *ia, TipoJugador *jugador, int dificultad);
#endif
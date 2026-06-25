void inicializar_instancias(TipoJugador *jugador, int id_asignado) {
    if (!jugador){
        manejar_error(ERR_PUNTERO_NULO, "guardar_turno verificacion inicial fallida."); return;
    }

    jugador->id = id_asignado;
    jugador->vidaTotal = 0;

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            jugador->tablero.matriz[i][j] = 0; 
        }
    }

    int vidas_base[MAX_BARCOS] = {5, 4, 3, 2, 2}; 

    for (int i = 0; i < MAX_BARCOS; i++) {
        jugador->barcos[i].vida = vidas_base[i];
        jugador->vidaTotal += jugador->barcos[i].vida;

        jugador->barcos[i].posX = -1;
        jugador->barcos[i].posY = -1;
        jugador->barcos[i].ancho = 0;
        jugador->barcos[i].largo = 0;
    }
}
void inicializar_jugador(TipoJugador *usuario, TipoJugador *bot) {
    printf("Inicializando sistemas...\n");

    inicializar_instancias(usuario, 1);

    inicializar_instancias(bot, 2);

    printf("¡Partida inicializada! Jugadores listos para anclar la flota.\n");
}

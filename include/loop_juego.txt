#include <stdio.h>
#include <stdlib.h>

/*

Inicio
InicializarJugador(jugador)
InicializarJugador(computadora)
SeleccionarDificultad()
PosicionarBarcos(jugador)
PosicionarBarcos(computadora)

while (jugador.vidaTotal > 0 AND computadora.vidaTotal > 0)

    MostrarMenuPartida()
    Leer(opcion)

    if (opcion == DISPARAR)
        Leer(x, y)

        while (CoordenadaValida(x,y) == FALSO)
            Mostrar("Coordenada inválida")
            Leer(x,y)
        end while

        Disparar(jugador, computadora, x, y)

        if (computadora.vidaTotal <= 0)
            break
        end if

        Mostrar("Turno de la computadora")
        coordenadaIA = GenerarMovimientoIA()

        Disparar(computadora, jugador,
                 coordenadaIA.x,
                 coordenadaIA.y)

    else if (opcion == MOSTRAR_TABLERO_PROPIO)

        MostrarTablero(jugador)

    else if (opcion == MOSTRAR_TABLERO_ATAQUES)

        MostrarTableroAtaques(jugador)

    else if (opcion == DESHACER)

        if (dificultad == FACIL)

            DeshacerMovimiento()

        else

            Mostrar("Opción no disponible")

        end if

    else

        Mostrar("Opción inválida")

    end if

end while

if (jugador.vidaTotal <= 0)

    Mostrar("Has sido derrotado")

else

    Mostrar("Ganador")

end if

LiberarMemoria()

Fin
*/


void loop_juego (){

    int dificultad = 0;
    int continuar = 0;

    while (1) {
        /* --- Inicializacion--- 
        1. Seleccion de dficultad
        2. Mostrar pantalla de juego
        3. Inicializar tablero jugador
        4. Inicializar tablero enemigo */
        dificultad = seleccion_dificultad(); //TODO
        inicializar_jugador();
        inicializar_enemigo(dificultad);

        continuar = partida();
        if (continuar == 0) break;

    } // while (1) FIN
}


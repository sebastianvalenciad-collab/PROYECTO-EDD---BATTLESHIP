# 🚢 BATTLESHIP — Proyecto EDD

## Descripción

Juego de Battleship (Batalla Naval) implementado en lenguaje C. Este trata de dos jugadores que se enfrentan en un tablero de 10×10, el usuario ubica sus barcos y luego dispara por turnos contra la IA para intentar hundir toda su flota antes de que ella hunda la tuya.

El juego maneja tres niveles de dificultad y utiliza estructuras de datos propias (listas enlazadas / pila) para el historial de movimientos.

---

## Cómo compilar y ejecutar

### Requisitos previos

- Tener instalado un compilador de C (`gcc`).
  - En **Linux / macOS**: generalmente ya viene instalado o se instala con `sudo apt install gcc` / `brew install gcc`.
  - En **Windows**: se recomienda instalar [MinGW](https://www.mingw-w64.org/) o usar el entorno [WSL](https://learn.microsoft.com/en-us/windows/wsl/).
- Opcionalmente, [Visual Studio Code](https://code.visualstudio.com/) con la extensión **C/C++ Extension Pack** de Microsoft.

### Pasos

1. Descarga y descomprime el archivo `.zip` en una carpeta de tu elección.

2. Abre una terminal en esa carpeta (o usa la terminal integrada de VS Code: `Terminal > Nueva terminal`).

3. Compila todos los archivos fuente:

```bash
gcc main.c funciones.c -Werror -o main
```
4. Ejecuta el programa:

```bash
./main
```

---

## Funcionalidades

### Funcionando correctamente

- Menú principal con opciones para empezar, ver instrucciones o salir.
- Selección de dificultad (Fácil, Media, Difícil).
- Colocación manual de los barcos del jugador en el tablero.
- Colocación automática aleatoria de los barcos de la IA.
- Tablero de 10×10 con coordenadas (filas 1–10, columnas A–J).
- Disparo por turnos, el jugador elige fila y columna, el sistema indica agua o impacto.
- Turno automático de la IA tras cada disparo del jugador.
- Visualización simultánea del tablero enemigo y el tablero propio durante la partida.
- Detección de victoria cuando todos los barcos enemigos son hundidos.
- IA en dificultad Fácil y Media (`ia_media`): dispara de forma aleatoria.

### En desarrollo / incompleto

- **Deshacer movimiento** EN ESPERA..
- **IA Difícil** modo "cazador" en espera..

---

## Ejemplo de uso

### Paso 1: Comenzar partida con la opcion E.
```
=========================================================
████   ███  █████ █████ █     █████  ████ █   █ ███ ████
...
=========================================================
PRESIONA E PARA EMPEZAR
PRESIONA I PARA INSTRUCCIONES
PRESIONA S PARA SALIR
```

### Paso 2: Selección de dificultad

```
=================================
      SELECCIONAR DIFICULTAD
=================================
1. Facil
2. Media
3. Dificil
=================================
Seleccione una opcion: 1
```

### Paso 3: Colocación de barcos (jugador)

El sistema te pedirá ubicar 5 barcos de distintos tamaños (5, 4, 3, 3 y 2 casillas). Para cada uno debes indicar:

- Columna (A–J)
  - Fila (1–10)
- Orientación: `H` (horizontal) o `V` (vertical)

### Paso 4: Comenzar el Juego atancando al enemigo con la opcion 1.
(Al igual que paso anterior se le pedira indicar Columna y Fila)

```
=========================================================
==================== TURNO: JUGADOR ====================
=========================================================
        TABLERO ENEMIGO              TABLERO PERSONAL
    A B C D E F G H I J          A B C D E F G H I J
 1  * * * * * * * * * *       1  B B B B B * * * * *
 2  * * * * * * * * * *       2  * * * * * * * * * *
...
=========================================================
=================================
     6     BATTLESHIPS
=================================
0. Salir al menu principal
1. Disparar
2. Deshacer movimiento   <-- solo en dificultad Fácil
=================================
```

### *Paso 5 (Dificultad Facil): Deshacer un movimiento equivocado.
(Esta funcion aplica solamente si previamente existen movimientos en dificultad facil)
---

## Notas

- Los barcos propios se muestran como `B`, el agua como `*` y los impactos como `X`.
- En el tablero enemigo no se ven los barcos hasta que son impactados, para respetar la mecánica del juego.
- Puedes salir de una partida en curso seleccionando la opción `0` en el menú de juego.

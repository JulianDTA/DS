#ifndef GAME_H
#define GAME_H

#include "combat.h"

// =====================================================
// ECUATRIALS - Maquina de Estados del Juego
// =====================================================

typedef enum {
    GAME_TITLE,         // Pantalla de titulo
    GAME_SELECT_CHAR,   // Seleccion de personaje
    GAME_COMBAT,        // Combate
    GAME_RESULT         // Pantalla de resultado (Victoria/Derrota)
} GamePhase;

typedef struct {
    GamePhase fase;
    int personaje_elegido;   // 0=Cantuna, 1=TinTin, 2=Tunda
    int rival_elegido;
    CombatState combate;
    bool isMainOnBottom;
} GameState;

// Inicializa el juego entero
void game_init(GameState* gs);

// Actualiza el juego (llamar cada frame)
void game_update(GameState* gs, int keys_down, touchPosition* touch);

// Dibuja la interfaz de texto
void game_draw(GameState* gs);

#endif

#ifndef GAME_H
#define GAME_H

#include "combat.h"

// =====================================================
// ECUATRIALS - Maquina de Estados del Juego
// =====================================================

typedef enum {
    GAME_TITLE,
    GAME_SELECT_CHAR,
    GAME_COMBAT,
    GAME_RESULT
} GamePhase;

typedef struct {
    GamePhase fase;
    int personaje_elegido;
    int rival_elegido;
    CombatState combate;
    bool isMainOnBottom;
    bool top_dirty;
    bool bottom_dirty;
} GameState;

void game_init(GameState* gs);
void game_update(GameState* gs, int keys_down, touchPosition* touch);
void game_draw_top(GameState* gs);
void game_draw_bottom(GameState* gs);

#endif

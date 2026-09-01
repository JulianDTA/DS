#ifndef COMBAT_H
#define COMBAT_H

#include "deck.h"
#include <stdbool.h>

// =====================================================
// ECUATRIALS - Gestor de Combate por Turnos
// =====================================================

typedef enum {
    COMBAT_START,
    COMBAT_PLAYER_DRAW,
    COMBAT_PLAYER_TURN,
    COMBAT_PLAYER_RESOLVE,
    COMBAT_ENEMY_TURN,
    COMBAT_ENEMY_WAIT,
    COMBAT_ENEMY_RESOLVE,
    COMBAT_CHECK_WIN,
    COMBAT_WIN,
    COMBAT_LOSE
} CombatPhase;

typedef struct {
    const char* nombre;
    int hp;
    int max_hp;
    DeckState deck;
    bool puede_jugar_otra;
    
    // Reglas / Auras activas
    const CardData* reglas_activas[3];
    int num_reglas;
} Fighter;

typedef struct {
    Fighter jugador;
    Fighter rival;
    CombatPhase fase;
    int turno;
    int cursor;
    bool carta_jugada_este_turno;
    bool ya_robo_turno;
    
    // Historial
    char log[10][32];
    int log_count;
    
    // Timer para pausas (ej. turno enemigo)
    int timer;
    
    // Drag & Drop Táctil
    int dragged_card_idx; // -1 si ninguna
    int drag_x;
    int drag_y;
    
} CombatState;

void combat_init(CombatState* cs,
                 const char* nombre_jugador, const CardData* deck_jugador, int deck_size_j,
                 const char* nombre_rival, const CardData* deck_rival, int deck_size_r);

void combat_update(CombatState* cs, int keys_down, touchPosition* touch);

void combat_resolve_card(CombatState* cs, Fighter* atacante, Fighter* defensor, const CardData* carta);

void combat_ai_turn(CombatState* cs);

void combat_log(CombatState* cs, const char* msg);

#endif

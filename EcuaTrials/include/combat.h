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
} Fighter;

typedef struct {
    Fighter jugador;
    Fighter rival;
    CombatPhase fase;
    int turno;
    int cursor;
    bool carta_jugada_este_turno;
    bool ya_robo_turno;
    int timer;
    
    char log[6][32];
    int log_count;
} CombatState;

void combat_init(CombatState* cs,
                 const char* nombre_jugador, const CardData* deck_jugador, int deck_size_j,
                 const char* nombre_rival, const CardData* deck_rival, int deck_size_r);

void combat_update(CombatState* cs, int keys_down);

void combat_resolve_card(CombatState* cs, Fighter* atacante, Fighter* defensor, const CardData* carta);

void combat_ai_turn(CombatState* cs);

void combat_log(CombatState* cs, const char* msg);

#endif

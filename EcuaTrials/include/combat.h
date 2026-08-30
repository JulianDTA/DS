#ifndef COMBAT_H
#define COMBAT_H

#include "deck.h"
#include <stdbool.h>

// =====================================================
// ECUATRIALS - Gestor de Combate por Turnos
// =====================================================

// Estados del combate
typedef enum {
    COMBAT_START,           // Animacion inicial
    COMBAT_PLAYER_DRAW,     // Jugador roba carta
    COMBAT_PLAYER_TURN,     // Jugador elige que carta jugar
    COMBAT_PLAYER_RESOLVE,  // Resolviendo efectos de la carta jugada
    COMBAT_ENEMY_TURN,      // IA del rival juega sus cartas
    COMBAT_ENEMY_RESOLVE,   // Resolviendo efectos del rival
    COMBAT_CHECK_WIN,       // Verificar si alguien murio
    COMBAT_WIN,             // Jugador gano
    COMBAT_LOSE             // Jugador perdio
} CombatPhase;

// Datos de un combatiente (Jugador o Rival)
typedef struct {
    const char* nombre;
    int hp;
    int max_hp;
    DeckState deck;
    bool puede_jugar_otra;  // Flag de "Jugar Otra Vez" (Rayo en Dungeon Mayhem)
} Fighter;

// Estado global del combate
typedef struct {
    Fighter jugador;
    Fighter rival;
    CombatPhase fase;
    int turno;              // Contador de turnos
    int cursor;             // Indice de la carta seleccionada en la mano
    bool carta_jugada_este_turno;
    
    // Log de texto para la pantalla
    char log[6][32];
    int log_count;
} CombatState;

// Inicializa un combate nuevo entre dos personajes
void combat_init(CombatState* cs, 
                 const char* nombre_jugador, const CardData* deck_jugador, int deck_size_j,
                 const char* nombre_rival, const CardData* deck_rival, int deck_size_r);

// Avanza la maquina de estados del combate (llamar cada frame)
void combat_update(CombatState* cs, int keys_down);

// Aplica los efectos de una carta jugada por un combatiente contra otro
void combat_resolve_card(CombatState* cs, Fighter* atacante, Fighter* defensor, const CardData* carta);

// IA simple del rival: elige y juega cartas
void combat_ai_turn(CombatState* cs);

// Escribe un mensaje en el log de combate
void combat_log(CombatState* cs, const char* msg);

#endif

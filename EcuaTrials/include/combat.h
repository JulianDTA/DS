#ifndef COMBAT_H
#define COMBAT_H

#include "card.h"
#include <stdbool.h>

// Estadísticas de los jugadores/leyendas en la partida
typedef struct {
    int hp;
    int max_hp;
    int shield;
    int energy;     // Energía actual para jugar cartas
    int max_energy; // Energía máxima
} PlayerState;

// Inicializa el estado del combate (10 HP, 0 escudos, etc.)
void init_combat(void);

// Juega una carta desde la mano, aplicando su costo y efectos
// Retorna true si se pudo jugar, false si no hay energía suficiente
bool play_card(int player_id, const CardData* card);

// Procesa el daño contra un jugador (golpea el escudo primero, luego el HP)
void take_damage(int target_id, int amount);

// Obtiene el estado actual de un jugador (0 = Jugador Local, 1 = Rival)
PlayerState* get_player_state(int player_id);

#endif

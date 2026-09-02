#ifndef DECK_H
#define DECK_H

#include "card.h"

// =====================================================
// ECUATRIALS - Sistema de Mazo, Mano, y Pila de Descarte
// =====================================================

typedef struct {
    // Mazo de robo (boca abajo)
    const CardData* mazo[MAX_DECK_SIZE];
    int mazo_top;  // Indice del tope del mazo (cuantas cartas quedan)
    
    // Mano del jugador
    const CardData* mano[MAX_HAND_SIZE];
    int mano_size;
    
    // Pila de descarte
    const CardData* descarte[MAX_DECK_SIZE];
    int descarte_size;
    
    // Escudos activos en el campo
    Shield escudos[MAX_SHIELDS];
    int escudos_activos;
    
} DeckState;

// Inicializa un mazo con las cartas de un personaje y lo baraja
void deck_init(DeckState* ds, const CardData* cartas, int num_cartas);

// Baraja el mazo
void deck_shuffle(DeckState* ds);

// Roba N cartas del mazo y las pone en la mano
// Si el mazo se queda vacio, recicla la pila de descarte
bool deck_draw(DeckState* ds, int n);

// Juega la carta en la posicion 'index' de la mano (la mueve al descarte)
const CardData* deck_play_from_hand(DeckState* ds, int index);

// Agrega un escudo al campo. Retorna true si se pudo colocar
bool deck_add_shield(DeckState* ds, int durabilidad);

// Aplica dano a los escudos del jugador. Retorna el dano sobrante (no absorbido)
int deck_damage_shields(DeckState* ds, int dano);

void deck_add_to_hand(DeckState* ds, const CardData* carta);
const CardData* deck_steal_random_from_hand(DeckState* ds);
const CardData* deck_steal_top_from_deck(DeckState* ds, bool* did_shuffle);
const CardData* deck_steal_random_from_discard(DeckState* ds);

int deck_get_total_shield(DeckState* ds);
#endif

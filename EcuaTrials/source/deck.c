#include "deck.h"
#include <stdlib.h>
#include <string.h>

// =====================================================
// Generador de numeros aleatorios simple para la DS
// =====================================================
static unsigned int rng_seed = 12345;
int deck_rng_next() {
    rng_seed = rng_seed * 1103515245 + 12345;
    return (rng_seed >> 16) & 0x7FFF;
}

void deck_init(DeckState* ds, const CardData* cartas, int num_cartas) {
    memset(ds, 0, sizeof(DeckState));
    
    // Copiar las cartas al mazo
    for (int i = 0; i < num_cartas && i < MAX_DECK_SIZE; i++) {
        ds->mazo[i] = &cartas[i];
    }
    ds->mazo_top = num_cartas;
    ds->mano_size = 0;
    ds->descarte_size = 0;
    ds->escudos_activos = 0;
    
    for (int i = 0; i < MAX_SHIELDS; i++) {
        ds->escudos[i].activo = false;
        ds->escudos[i].durabilidad = 0;
    }
    
    // Sembrar la semilla con el timer de la DS
    rng_seed = (unsigned int)(REG_VCOUNT * 7919 + 42);
    
    deck_shuffle(ds);
}

void deck_shuffle(DeckState* ds) {
    // Fisher-Yates shuffle
    for (int i = ds->mazo_top - 1; i > 0; i--) {
        int j = deck_rng_next() % (i + 1);
        const CardData* temp = ds->mazo[i];
        ds->mazo[i] = ds->mazo[j];
        ds->mazo[j] = temp;
    }
}

bool deck_draw(DeckState* ds, int n) {
    bool shuffled = false;
    for (int i = 0; i < n; i++) {
        if (ds->mano_size >= MAX_HAND_SIZE) return shuffled;
        
        if (ds->mazo_top <= 0) {
            if (ds->descarte_size <= 0) return shuffled;
            
            for (int j = 0; j < ds->descarte_size; j++) {
                ds->mazo[j] = ds->descarte[j];
            }
            ds->mazo_top = ds->descarte_size;
            ds->descarte_size = 0;
            
            deck_shuffle(ds);
            shuffled = true;
        }
        
        // Robar la carta del tope
        ds->mazo_top--;
        ds->mano[ds->mano_size] = ds->mazo[ds->mazo_top];
        ds->mano_size++;
    }
    return shuffled;
}

const CardData* deck_play_from_hand(DeckState* ds, int index) {
    if (index < 0 || index >= ds->mano_size) return NULL;
    
    const CardData* carta = ds->mano[index];
    
    // Mover la carta al descarte
    if (ds->descarte_size < MAX_DECK_SIZE) {
        ds->descarte[ds->descarte_size] = carta;
        ds->descarte_size++;
    }
    
    // Cerrar el hueco en la mano (desplazar las cartas)
    for (int i = index; i < ds->mano_size - 1; i++) {
        ds->mano[i] = ds->mano[i + 1];
    }
    ds->mano_size--;
    
    return carta;
}

bool deck_add_shield(DeckState* ds, int durabilidad) {
    for (int i = 0; i < MAX_SHIELDS; i++) {
        if (!ds->escudos[i].activo) {
            ds->escudos[i].activo = true;
            ds->escudos[i].durabilidad = durabilidad;
            ds->escudos_activos++;
            return true;
        }
    }
    return false; // No hay espacio para mas escudos
}

int deck_damage_shields(DeckState* ds, int dano) {
    // Repartir el dano entre los escudos activos
    for (int i = 0; i < MAX_SHIELDS && dano > 0; i++) {
        if (ds->escudos[i].activo) {
            if (dano >= ds->escudos[i].durabilidad) {
                dano -= ds->escudos[i].durabilidad;
                ds->escudos[i].activo = false;
                ds->escudos[i].durabilidad = 0;
                ds->escudos_activos--;
            } else {
                ds->escudos[i].durabilidad -= dano;
                dano = 0;
            }
        }
    }
    return dano; // Retorna el dano que paso al HP
}

void deck_add_to_hand(DeckState* ds, const CardData* carta) {
    if (!carta) return;
    if (ds->mano_size >= MAX_HAND_SIZE) {
        if (ds->descarte_size < MAX_DECK_SIZE) {
            ds->descarte[ds->descarte_size] = carta;
            ds->descarte_size++;
        }
    } else {
        ds->mano[ds->mano_size] = carta;
        ds->mano_size++;
    }
}

const CardData* deck_steal_random_from_hand(DeckState* ds) {
    if (ds->mano_size <= 0) return NULL;
    int idx = deck_rng_next() % ds->mano_size;
    const CardData* carta = ds->mano[idx];
    for (int i = idx; i < ds->mano_size - 1; i++) {
        ds->mano[i] = ds->mano[i + 1];
    }
    ds->mano_size--;
    return carta;
}

const CardData* deck_steal_top_from_deck(DeckState* ds, bool* did_shuffle) {
    if (did_shuffle) *did_shuffle = false;
    if (ds->mazo_top <= 0) {
        if (ds->descarte_size <= 0) return NULL;
        if (did_shuffle) *did_shuffle = true;
        for (int j = 0; j < ds->descarte_size; j++) {
            ds->mazo[j] = ds->descarte[j];
        }
        ds->mazo_top = ds->descarte_size;
        ds->descarte_size = 0;
        deck_shuffle(ds);
    }
    if (ds->mazo_top <= 0) return NULL;
    ds->mazo_top--;
    return ds->mazo[ds->mazo_top];
}

const CardData* deck_steal_random_from_discard(DeckState* ds) {
    if (ds->descarte_size <= 0) return NULL;
    int idx = deck_rng_next() % ds->descarte_size;
    const CardData* carta = ds->descarte[idx];
    for (int i = idx; i < ds->descarte_size - 1; i++) {
        ds->descarte[i] = ds->descarte[i + 1];
    }
    ds->descarte_size--;
    return carta;
}

int deck_get_total_shield(DeckState* ds) {
    int total = 0;
    for (int i=0; i<MAX_SHIELDS; i++) {
        if (ds->escudos[i].activo) total += ds->escudos[i].durabilidad;
    }
    return total;
}

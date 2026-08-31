#ifndef CARD_H
#define CARD_H

#include <nds.h>
#include <stdbool.h>

// =====================================================
// ECUATRIALS - Sistema de Cartas
// =====================================================

// Tipos de efecto que una carta puede tener (una carta puede tener varios)
#define FX_ATTACK       (1 << 0)
#define FX_SHIELD       (1 << 1)
#define FX_HEAL         (1 << 2)
#define FX_DRAW         (1 << 3)
#define FX_PLAY_AGAIN   (1 << 4)
#define FX_STEAL_HAND   (1 << 5)
#define FX_STEAL_DECK   (1 << 6)
#define FX_STEAL_DISCARD (1 << 7)  // Rayo: Juega otra carta gratis

// Maximo de cartas en un mazo
#define MAX_DECK_SIZE 28
// Maximo de cartas en la mano
#define MAX_HAND_SIZE 10
// Maximo de escudos activos en el campo
#define MAX_SHIELDS   5

// Estructura de una carta
typedef struct {
    int id;
    const char* nombre;
    int efectos;        // Bitmask de FX_*
    int ataque;         // Puntos de dano
    int escudo;         // Puntos de escudo que otorga
    int curacion;       // Puntos de HP que cura
    int robar;          // Cantidad de cartas que roba
    const char* lore1;  // Linea 1 del lore
    const char* lore2;  // Linea 2 del lore
    const char* lore3;  // Linea 3 del lore
} CardData;

// Escudo activo en el campo
typedef struct {
    bool activo;
    int durabilidad;    // Cuantos golpes aguanta
} Shield;

// Base de datos de todas las cartas del juego
extern const CardData CARTAS_CANTUNA[];
extern const int CANTUNA_DECK_SIZE;
extern const CardData CARTAS_TINTIN[];
extern const int TINTIN_DECK_SIZE;
extern const CardData CARTAS_TUNDA[];
extern const int TUNDA_DECK_SIZE;
extern const CardData CARTAS_ALMEIDA[];
extern const int ALMEIDA_DECK_SIZE;
extern const CardData CARTAS_DAMATAPADA[];
extern const int DAMATAPADA_DECK_SIZE;
extern const CardData CARTAS_MARIANGULA[];
extern const int MARIANGULA_DECK_SIZE;
extern const CardData CARTAS_GALLO[];
extern const int GALLO_DECK_SIZE;
extern const CardData CARTAS_CURA[];
extern const int CURA_DECK_SIZE;
extern const CardData CARTAS_CHUZALONGO[];
extern const int CHUZALONGO_DECK_SIZE;
extern const CardData CARTAS_LLORONA[];
extern const int LLORONA_DECK_SIZE;
extern const CardData CARTAS_GUAGUAAUCA[];
extern const int GUAGUAAUCA_DECK_SIZE;
extern const CardData CARTAS_VIUDA[];
extern const int VIUDA_DECK_SIZE;

#endif

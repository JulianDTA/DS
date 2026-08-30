#ifndef CARD_H
#define CARD_H

#include <nds.h>
#include <stdbool.h>

// =====================================================
// ECUATRIALS - Sistema de Cartas
// Inspirado en Dungeon Mayhem + Hearthstone
// =====================================================

// Tipos de efecto que una carta puede tener (una carta puede tener varios)
#define FX_ATTACK     (1 << 0)  // Espadas cruzadas: Hace dano
#define FX_SHIELD     (1 << 1)  // Escudo: Protege del dano
#define FX_HEAL       (1 << 2)  // Corazon: Cura vida
#define FX_DRAW       (1 << 3)  // Carta: Roba cartas adicionales
#define FX_PLAY_AGAIN (1 << 4)  // Rayo: Juega otra carta gratis

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
} CardData;

// Escudo activo en el campo
typedef struct {
    bool activo;
    int durabilidad;    // Cuantos golpes aguanta (cada golpe = -1)
} Shield;

// Base de datos de todas las cartas del juego
extern const CardData CARTAS_CANTUNA[];
extern const int CANTUNA_DECK_SIZE;

extern const CardData CARTAS_TINTIN[];
extern const int TINTIN_DECK_SIZE;

extern const CardData CARTAS_TUNDA[];
extern const int TUNDA_DECK_SIZE;

#endif

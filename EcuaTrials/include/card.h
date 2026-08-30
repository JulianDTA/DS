#ifndef CARD_H
#define CARD_H

#include <nds.h>

// Definición de estadísticas de las cartas de EcuaTrials
typedef struct {
    int id;
    const char* nombre;
    int costo;
    int damage;
    int heal;
    int defense;
    
    // Coordenadas para el motor 3D (Texturas)
    float u_start, v_start;
    float u_end, v_end;
    
    // Color de tinte (R, G, B)
    u8 r, g, b;
} CardData;

// Base de datos (Core Set) inicial
extern const CardData CartaDB[];

#endif

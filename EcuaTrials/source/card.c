#include "card.h"

// =====================================================
// MAZO DE CANTUNA (28 cartas)
// Estilo: Tanque/Constructor - Muchos escudos y golpes fuertes
// =====================================================
const CardData CARTAS_CANTUNA[] = {
    // Ataques puros (8 cartas)
    {0, "Ladrillazo",         FX_ATTACK,                3, 0, 0, 0},
    {0, "Ladrillazo",         FX_ATTACK,                3, 0, 0, 0},
    {0, "Ladrillazo",         FX_ATTACK,                3, 0, 0, 0},
    {1, "Golpe de Piedra",    FX_ATTACK,                2, 0, 0, 0},
    {1, "Golpe de Piedra",    FX_ATTACK,                2, 0, 0, 0},
    {1, "Golpe de Piedra",    FX_ATTACK,                2, 0, 0, 0},
    {2, "Avalancha",          FX_ATTACK,                5, 0, 0, 0},
    {2, "Avalancha",          FX_ATTACK,                5, 0, 0, 0},
    
    // Escudos (6 cartas)
    {3, "Muro de Piedra",     FX_SHIELD,                0, 2, 0, 0},
    {3, "Muro de Piedra",     FX_SHIELD,                0, 2, 0, 0},
    {3, "Muro de Piedra",     FX_SHIELD,                0, 2, 0, 0},
    {4, "Fortaleza",          FX_SHIELD,                0, 3, 0, 0},
    {4, "Fortaleza",          FX_SHIELD,                0, 3, 0, 0},
    {4, "Fortaleza",          FX_SHIELD,                0, 3, 0, 0},
    
    // Curacion (4 cartas)
    {5, "Descanso",           FX_HEAL,                  0, 0, 2, 0},
    {5, "Descanso",           FX_HEAL,                  0, 0, 2, 0},
    {6, "Pacto Diabolico",    FX_HEAL,                  0, 0, 4, 0},
    {6, "Pacto Diabolico",    FX_HEAL,                  0, 0, 4, 0},
    
    // Robo de cartas (4 cartas)
    {7, "Planos Secretos",    FX_DRAW,                  0, 0, 0, 2},
    {7, "Planos Secretos",    FX_DRAW,                  0, 0, 0, 2},
    {8, "Inspiracion",        FX_DRAW | FX_PLAY_AGAIN,  0, 0, 0, 1},
    {8, "Inspiracion",        FX_DRAW | FX_PLAY_AGAIN,  0, 0, 0, 1},
    
    // Combos (6 cartas)
    {9,  "Contraataque",      FX_ATTACK | FX_SHIELD,    2, 1, 0, 0},
    {9,  "Contraataque",      FX_ATTACK | FX_SHIELD,    2, 1, 0, 0},
    {10, "Furia del Constructor", FX_ATTACK | FX_PLAY_AGAIN, 2, 0, 0, 0},
    {10, "Furia del Constructor", FX_ATTACK | FX_PLAY_AGAIN, 2, 0, 0, 0},
    {11, "Bendicion Oscura",  FX_HEAL | FX_DRAW,        0, 0, 2, 1},
    {11, "Bendicion Oscura",  FX_HEAL | FX_DRAW,        0, 0, 2, 1},
};
const int CANTUNA_DECK_SIZE = 28;

// =====================================================
// MAZO DE EL TIN TIN (28 cartas)
// Estilo: Agresor/Rapido - Muchos ataques y robos de carta
// =====================================================
const CardData CARTAS_TINTIN[] = {
    // Ataques (10 cartas) - Muchos ataques rapidos
    {20, "Travesura",         FX_ATTACK,                2, 0, 0, 0},
    {20, "Travesura",         FX_ATTACK,                2, 0, 0, 0},
    {20, "Travesura",         FX_ATTACK,                2, 0, 0, 0},
    {20, "Travesura",         FX_ATTACK,                2, 0, 0, 0},
    {21, "Sombrerazo",        FX_ATTACK,                3, 0, 0, 0},
    {21, "Sombrerazo",        FX_ATTACK,                3, 0, 0, 0},
    {21, "Sombrerazo",        FX_ATTACK,                3, 0, 0, 0},
    {22, "Emboscada",         FX_ATTACK,                4, 0, 0, 0},
    {22, "Emboscada",         FX_ATTACK,                4, 0, 0, 0},
    {22, "Emboscada",         FX_ATTACK,                4, 0, 0, 0},
    
    // Escudos (3 cartas) - Pocos, es agresivo
    {23, "Escondite",         FX_SHIELD,                0, 1, 0, 0},
    {23, "Escondite",         FX_SHIELD,                0, 1, 0, 0},
    {23, "Escondite",         FX_SHIELD,                0, 1, 0, 0},
    
    // Curacion (2 cartas) - Casi nada
    {24, "Siesta Maliciosa",  FX_HEAL,                  0, 0, 2, 0},
    {24, "Siesta Maliciosa",  FX_HEAL,                  0, 0, 2, 0},
    
    // Robo y velocidad (7 cartas)
    {25, "Robo de Bolsillos",  FX_DRAW,                 0, 0, 0, 2},
    {25, "Robo de Bolsillos",  FX_DRAW,                 0, 0, 0, 2},
    {25, "Robo de Bolsillos",  FX_DRAW,                 0, 0, 0, 2},
    {26, "Agilidad",           FX_DRAW | FX_PLAY_AGAIN, 0, 0, 0, 1},
    {26, "Agilidad",           FX_DRAW | FX_PLAY_AGAIN, 0, 0, 0, 1},
    {26, "Agilidad",           FX_DRAW | FX_PLAY_AGAIN, 0, 0, 0, 1},
    {26, "Agilidad",           FX_DRAW | FX_PLAY_AGAIN, 0, 0, 0, 1},
    
    // Combos (6 cartas)
    {27, "Golpe Fugaz",        FX_ATTACK | FX_PLAY_AGAIN, 2, 0, 0, 0},
    {27, "Golpe Fugaz",        FX_ATTACK | FX_PLAY_AGAIN, 2, 0, 0, 0},
    {27, "Golpe Fugaz",        FX_ATTACK | FX_PLAY_AGAIN, 2, 0, 0, 0},
    {28, "Ataque Sorpresa",    FX_ATTACK | FX_DRAW,       3, 0, 0, 1},
    {28, "Ataque Sorpresa",    FX_ATTACK | FX_DRAW,       3, 0, 0, 1},
    {28, "Ataque Sorpresa",    FX_ATTACK | FX_DRAW,       3, 0, 0, 1},
};
const int TINTIN_DECK_SIZE = 28;

// =====================================================
// MAZO DE LA TUNDA (28 cartas)
// Estilo: Control/Bruja - Curacion y efectos mixtos
// =====================================================
const CardData CARTAS_TUNDA[] = {
    // Ataques (6 cartas)
    {40, "Zarpazo",           FX_ATTACK,                3, 0, 0, 0},
    {40, "Zarpazo",           FX_ATTACK,                3, 0, 0, 0},
    {40, "Zarpazo",           FX_ATTACK,                3, 0, 0, 0},
    {41, "Molinillazo",       FX_ATTACK,                4, 0, 0, 0},
    {41, "Molinillazo",       FX_ATTACK,                4, 0, 0, 0},
    {41, "Molinillazo",       FX_ATTACK,                4, 0, 0, 0},
    
    // Escudos (4 cartas)
    {42, "Niebla Espesa",     FX_SHIELD,                0, 2, 0, 0},
    {42, "Niebla Espesa",     FX_SHIELD,                0, 2, 0, 0},
    {42, "Niebla Espesa",     FX_SHIELD,                0, 2, 0, 0},
    {42, "Niebla Espesa",     FX_SHIELD,                0, 2, 0, 0},
    
    // Curacion (8 cartas) - Su especialidad
    {43, "Camarones Magicos", FX_HEAL,                  0, 0, 2, 0},
    {43, "Camarones Magicos", FX_HEAL,                  0, 0, 2, 0},
    {43, "Camarones Magicos", FX_HEAL,                  0, 0, 2, 0},
    {43, "Camarones Magicos", FX_HEAL,                  0, 0, 2, 0},
    {44, "Ritual de Sanacion",FX_HEAL,                  0, 0, 4, 0},
    {44, "Ritual de Sanacion",FX_HEAL,                  0, 0, 4, 0},
    {44, "Ritual de Sanacion",FX_HEAL,                  0, 0, 4, 0},
    {44, "Ritual de Sanacion",FX_HEAL,                  0, 0, 4, 0},
    
    // Robo (4 cartas)
    {45, "Susurros",          FX_DRAW,                  0, 0, 0, 2},
    {45, "Susurros",          FX_DRAW,                  0, 0, 0, 2},
    {46, "Encantamiento",     FX_DRAW | FX_PLAY_AGAIN,  0, 0, 0, 1},
    {46, "Encantamiento",     FX_DRAW | FX_PLAY_AGAIN,  0, 0, 0, 1},
    
    // Combos (6 cartas)
    {47, "Drenar Vida",       FX_ATTACK | FX_HEAL,      2, 0, 2, 0},
    {47, "Drenar Vida",       FX_ATTACK | FX_HEAL,      2, 0, 2, 0},
    {47, "Drenar Vida",       FX_ATTACK | FX_HEAL,      2, 0, 2, 0},
    {48, "Maldicion",         FX_ATTACK | FX_SHIELD,    3, 1, 0, 0},
    {48, "Maldicion",         FX_ATTACK | FX_SHIELD,    3, 1, 0, 0},
    {48, "Maldicion",         FX_ATTACK | FX_SHIELD,    3, 1, 0, 0},
};
const int TUNDA_DECK_SIZE = 28;

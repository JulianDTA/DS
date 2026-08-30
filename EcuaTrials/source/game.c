#include "game.h"
#include <stdio.h>
#include <string.h>

// =====================================================
// ECUATRIALS - Flujo del Juego Completo
// =====================================================

static const char* NOMBRES_PERSONAJES[] = {"Cantuna", "Tin Tin", "La Tunda"};

static const CardData* get_deck_for_char(int id) {
    switch(id) {
        case 0: return CARTAS_CANTUNA;
        case 1: return CARTAS_TINTIN;
        case 2: return CARTAS_TUNDA;
        default: return CARTAS_CANTUNA;
    }
}

static int get_deck_size_for_char(int id) {
    switch(id) {
        case 0: return CANTUNA_DECK_SIZE;
        case 1: return TINTIN_DECK_SIZE;
        case 2: return TUNDA_DECK_SIZE;
        default: return CANTUNA_DECK_SIZE;
    }
}

void game_init(GameState* gs) {
    memset(gs, 0, sizeof(GameState));
    gs->fase = GAME_TITLE;
    gs->personaje_elegido = 0;
    gs->rival_elegido = 1;
    gs->isMainOnBottom = false;
}

void game_update(GameState* gs, int keys_down, touchPosition* touch) {
    // Intercambio de pantallas (siempre disponible)
    if (keys_down & KEY_SELECT) {
        gs->isMainOnBottom = !gs->isMainOnBottom;
        if (gs->isMainOnBottom) lcdMainOnBottom();
        else lcdMainOnTop();
    }
    
    switch (gs->fase) {
        case GAME_TITLE:
            if (keys_down & KEY_START) {
                gs->fase = GAME_SELECT_CHAR;
            }
            break;
            
        case GAME_SELECT_CHAR:
            if (keys_down & KEY_LEFT) {
                gs->personaje_elegido--;
                if (gs->personaje_elegido < 0) gs->personaje_elegido = 2;
            }
            if (keys_down & KEY_RIGHT) {
                gs->personaje_elegido++;
                if (gs->personaje_elegido > 2) gs->personaje_elegido = 0;
            }
            
            if (keys_down & KEY_A) {
                // Elegir un rival aleatorio diferente al jugador
                gs->rival_elegido = (gs->personaje_elegido + 1) % 3;
                
                combat_init(&gs->combate,
                    NOMBRES_PERSONAJES[gs->personaje_elegido],
                    get_deck_for_char(gs->personaje_elegido),
                    get_deck_size_for_char(gs->personaje_elegido),
                    NOMBRES_PERSONAJES[gs->rival_elegido],
                    get_deck_for_char(gs->rival_elegido),
                    get_deck_size_for_char(gs->rival_elegido));
                    
                gs->fase = GAME_COMBAT;
            }
            
            if (keys_down & KEY_B) {
                gs->fase = GAME_TITLE;
            }
            break;
            
        case GAME_COMBAT:
            combat_update(&gs->combate, keys_down);
            
            if (gs->combate.fase == COMBAT_WIN || gs->combate.fase == COMBAT_LOSE) {
                if (keys_down & KEY_START) {
                    gs->fase = GAME_RESULT;
                }
            }
            break;
            
        case GAME_RESULT:
            if (keys_down & KEY_START) {
                gs->fase = GAME_TITLE;
            }
            break;
    }
}

void game_draw(GameState* gs) {
    consoleClear();
    
    switch (gs->fase) {
        case GAME_TITLE:
            printf("\n\n\n\n\n");
            printf("    ========================\n");
            printf("       E C U A T R I A L S\n");
            printf("    ========================\n\n");
            printf("    Leyendas Ecuatorianas\n");
            printf("    Juego de Cartas\n\n\n");
            printf("    Presiona START\n");
            printf("    para comenzar\n\n");
            printf("    SELECT: Cambiar pantalla\n");
            break;
            
        case GAME_SELECT_CHAR: {
            printf("\n\n   ELIGE TU LEYENDA\n\n");
            
            for (int i = 0; i < 3; i++) {
                if (i == gs->personaje_elegido) {
                    printf("   > %s <\n", NOMBRES_PERSONAJES[i]);
                } else {
                    printf("     %s\n", NOMBRES_PERSONAJES[i]);
                }
            }
            
            printf("\n");
            
            // Mostrar descripcion del personaje seleccionado
            switch (gs->personaje_elegido) {
                case 0:
                    printf("   CANTUNA\n");
                    printf("   Rol: Tanque\n");
                    printf("   Escudos fuertes y\n");
                    printf("   golpes devastadores.\n");
                    break;
                case 1:
                    printf("   EL TIN TIN\n");
                    printf("   Rol: Agresor\n");
                    printf("   Ataques rapidos y\n");
                    printf("   cadenas de combos.\n");
                    break;
                case 2:
                    printf("   LA TUNDA\n");
                    printf("   Rol: Control\n");
                    printf("   Curacion poderosa y\n");
                    printf("   drenaje de vida.\n");
                    break;
            }
            
            printf("\n   A: Elegir  B: Volver\n");
            printf("   </>: Cambiar\n");
            break;
        }
        
        case GAME_COMBAT: {
            CombatState* cs = &gs->combate;
            
            // --- BARRA DE ESTADO SUPERIOR ---
            printf(" TU(%s) HP:%d  Esc:", cs->jugador.nombre, cs->jugador.hp);
            // Contar escudos
            int esc_total = 0;
            for (int i = 0; i < MAX_SHIELDS; i++) {
                if (cs->jugador.deck.escudos[i].activo)
                    esc_total += cs->jugador.deck.escudos[i].durabilidad;
            }
            printf("%d\n", esc_total);
            
            printf(" VS(%s) HP:%d  Esc:", cs->rival.nombre, cs->rival.hp);
            int esc_rival = 0;
            for (int i = 0; i < MAX_SHIELDS; i++) {
                if (cs->rival.deck.escudos[i].activo)
                    esc_rival += cs->rival.deck.escudos[i].durabilidad;
            }
            printf("%d\n", esc_rival);
            
            printf(" Turno:%d  Mazo:%d  Desc:%d\n",
                cs->turno, cs->jugador.deck.mazo_top, cs->jugador.deck.descarte_size);
            printf("------------------------------\n");
            
            // --- LOG DE COMBATE ---
            for (int i = 0; i < cs->log_count && i < 6; i++) {
                printf(" %s\n", cs->log[i]);
            }
            // Rellenar lineas vacias del log
            for (int i = cs->log_count; i < 6; i++) {
                printf("\n");
            }
            
            printf("------------------------------\n");
            
            // --- MANO DEL JUGADOR ---
            if (cs->fase == COMBAT_PLAYER_TURN) {
                printf(" TU MANO (%d):\n", cs->jugador.deck.mano_size);
                
                for (int i = 0; i < cs->jugador.deck.mano_size; i++) {
                    const CardData* c = cs->jugador.deck.mano[i];
                    
                    if (i == cs->cursor) {
                        printf(">[%s]", c->nombre);
                    } else {
                        printf(" [%s]", c->nombre);
                    }
                    
                    // Iconos de efecto
                    if (c->efectos & FX_ATTACK)     printf(" A%d", c->ataque);
                    if (c->efectos & FX_SHIELD)     printf(" E%d", c->escudo);
                    if (c->efectos & FX_HEAL)       printf(" C%d", c->curacion);
                    if (c->efectos & FX_DRAW)       printf(" R%d", c->robar);
                    if (c->efectos & FX_PLAY_AGAIN) printf(" +");
                    printf("\n");
                }
                
                printf("\n A:Jugar B:Pasar Turno\n");
            } else if (cs->fase == COMBAT_WIN) {
                printf("\n   VICTORIA!\n");
                printf("   START: Continuar\n");
            } else if (cs->fase == COMBAT_LOSE) {
                printf("\n   DERROTA...\n");
                printf("   START: Continuar\n");
            } else {
                printf("\n Procesando...\n");
            }
            break;
        }
        
        case GAME_RESULT:
            printf("\n\n\n\n\n");
            if (gs->combate.fase == COMBAT_WIN) {
                printf("   FELICIDADES!\n\n");
                printf("   %s ha vencido\n", NOMBRES_PERSONAJES[gs->personaje_elegido]);
                printf("   a %s!\n\n", NOMBRES_PERSONAJES[gs->rival_elegido]);
            } else {
                printf("   HAS CAIDO...\n\n");
                printf("   %s fue derrotado\n", NOMBRES_PERSONAJES[gs->personaje_elegido]);
                printf("   por %s.\n\n", NOMBRES_PERSONAJES[gs->rival_elegido]);
            }
            printf("   START: Menu Principal\n");
            break;
    }
}

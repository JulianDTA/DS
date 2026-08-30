#include "game.h"
#include <stdio.h>
#include <string.h>

// =====================================================
// ECUATRIALS - Flujo del Juego + Pantalla de Lore
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

// =====================================================
// PANTALLA SUPERIOR: Descripcion y lore de la carta seleccionada
// =====================================================
void game_draw_top(GameState* gs) {
    consoleClear();

    switch (gs->fase) {
        case GAME_TITLE:
            printf("\n\n\n\n\n");
            printf("    ========================\n");
            printf("       E C U A T R I A L S\n");
            printf("    ========================\n\n");
            printf("    Leyendas Ecuatorianas\n");
            printf("    Juego de Cartas\n\n");
            printf("    Inspirado en\n");
            printf("    Dungeon Mayhem\n\n");
            printf("    v0.2 - 2026\n");
            break;

        case GAME_SELECT_CHAR:
            printf("\n\n");
            switch (gs->personaje_elegido) {
                case 0:
                    printf("   ========================\n");
                    printf("        C A N T U N A\n");
                    printf("   ========================\n\n");
                    printf("   Cuenta la leyenda que\n");
                    printf("   Cantuna hizo un pacto\n");
                    printf("   con el diablo para\n");
                    printf("   construir la Iglesia de\n");
                    printf("   San Francisco en Quito\n");
                    printf("   en una sola noche.\n\n");
                    printf("   Pero el astuto constructor\n");
                    printf("   quito un ladrillo antes\n");
                    printf("   del amanecer, y el diablo\n");
                    printf("   no pudo reclamar su alma.\n\n");
                    printf("   Rol: TANQUE\n");
                    printf("   Escudos fuertes, golpes\n");
                    printf("   devastadores.\n");
                    break;
                case 1:
                    printf("   ========================\n");
                    printf("       E L  T I N  T I N\n");
                    printf("   ========================\n\n");
                    printf("   Un duende travieso de la\n");
                    printf("   sierra ecuatoriana.\n");
                    printf("   Usa un sombrero enorme\n");
                    printf("   y aparece en los caminos\n");
                    printf("   oscuros para asustar a\n");
                    printf("   los viajeros solitarios.\n\n");
                    printf("   Es rapido, escurridizo,\n");
                    printf("   y le encanta robar cosas\n");
                    printf("   de los bolsillos.\n\n");
                    printf("   Rol: AGRESOR\n");
                    printf("   Ataques rapidos, cadenas\n");
                    printf("   de combos.\n");
                    break;
                case 2:
                    printf("   ========================\n");
                    printf("       L A  T U N D A\n");
                    printf("   ========================\n\n");
                    printf("   Espiritu femenino de la\n");
                    printf("   costa esmeraldena. Tiene\n");
                    printf("   una pierna normal y otra\n");
                    printf("   de molinillo de madera.\n\n");
                    printf("   Atrae a los ninos al\n");
                    printf("   manglar ofreciendoles\n");
                    printf("   camarones, y los hipnotiza\n");
                    printf("   con cantos ancestrales.\n\n");
                    printf("   Rol: CONTROL\n");
                    printf("   Curacion poderosa,\n");
                    printf("   drenaje de vida.\n");
                    break;
            }
            break;

        case GAME_COMBAT: {
            CombatState* cs = &gs->combate;

            if (cs->fase == COMBAT_PLAYER_TURN &&
                cs->jugador.deck.mano_size > 0 &&
                cs->cursor >= 0 && cs->cursor < cs->jugador.deck.mano_size)
            {
                const CardData* c = cs->jugador.deck.mano[cs->cursor];

                printf("\n");
                printf("   ========================\n");
                printf("    %s\n", c->nombre);
                printf("   ========================\n\n");

                // Iconos de efecto
                printf("   Efectos:\n");
                if (c->efectos & FX_ATTACK)
                    printf("   * Ataque: %d dano\n", c->ataque);
                if (c->efectos & FX_SHIELD)
                    printf("   * Escudo: %d puntos\n", c->escudo);
                if (c->efectos & FX_HEAL)
                    printf("   * Curacion: %d HP\n", c->curacion);
                if (c->efectos & FX_DRAW)
                    printf("   * Robar: %d carta(s)\n", c->robar);
                if (c->efectos & FX_PLAY_AGAIN)
                    printf("   * Encadenar: Juega otra!\n");

                printf("\n   ---- Lore ----\n\n");
                printf("   %s\n", c->lore1);
                printf("   %s\n", c->lore2);
                printf("   %s\n", c->lore3);

                printf("\n   ------- Controles -------\n");
                printf("   A: Jugar esta carta\n");
                if (!cs->ya_robo_turno && !cs->carta_jugada_este_turno)
                    printf("   X: Robar 1 carta\n");
                printf("   </>: Cambiar seleccion\n");
            } else if (cs->fase == COMBAT_WIN) {
                printf("\n\n\n\n\n");
                printf("   ========================\n");
                printf("       V I C T O R I A !\n");
                printf("   ========================\n\n");
                printf("   Tu leyenda ha triunfado.\n\n");
                printf("   START: Continuar\n");
            } else if (cs->fase == COMBAT_LOSE) {
                printf("\n\n\n\n\n");
                printf("   ========================\n");
                printf("       D E R R O T A\n");
                printf("   ========================\n\n");
                printf("   Tu leyenda ha caido.\n\n");
                printf("   START: Continuar\n");
            } else {
                printf("\n\n\n\n");
                printf("   Esperando...\n");
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

// =====================================================
// PANTALLA INFERIOR: HUD de combate y mano de cartas
// =====================================================
void game_draw_bottom(GameState* gs) {
    consoleClear();

    switch (gs->fase) {
        case GAME_TITLE:
            printf("\n\n\n\n\n\n\n\n");
            printf("      Presiona START\n");
            printf("      para comenzar\n\n");
            printf("    SELECT: Cambiar pantalla\n");
            break;

        case GAME_SELECT_CHAR:
            printf("\n\n   ELIGE TU LEYENDA\n\n");

            for (int i = 0; i < 3; i++) {
                if (i == gs->personaje_elegido) {
                    printf("   >> %s <<\n", NOMBRES_PERSONAJES[i]);
                } else {
                    printf("      %s\n", NOMBRES_PERSONAJES[i]);
                }
            }

            printf("\n   A: Elegir  B: Volver\n");
            printf("   </>: Cambiar leyenda\n");
            break;

        case GAME_COMBAT: {
            CombatState* cs = &gs->combate;

            // --- BARRA DE ESTADO ---
            printf(" TU(%s) HP:%d", cs->jugador.nombre, cs->jugador.hp);
            int esc_total = 0;
            for (int i = 0; i < MAX_SHIELDS; i++) {
                if (cs->jugador.deck.escudos[i].activo)
                    esc_total += cs->jugador.deck.escudos[i].durabilidad;
            }
            printf(" Esc:%d\n", esc_total);

            printf(" VS(%s) HP:%d", cs->rival.nombre, cs->rival.hp);
            int esc_rival = 0;
            for (int i = 0; i < MAX_SHIELDS; i++) {
                if (cs->rival.deck.escudos[i].activo)
                    esc_rival += cs->rival.deck.escudos[i].durabilidad;
            }
            printf(" Esc:%d\n", esc_rival);

            printf(" T:%d Mazo:%d Desc:%d\n",
                cs->turno, cs->jugador.deck.mazo_top, cs->jugador.deck.descarte_size);
            printf("------------------------------\n");

            // --- LOG ---
            for (int i = 0; i < cs->log_count && i < 6; i++) {
                printf(" %s\n", cs->log[i]);
            }
            for (int i = cs->log_count; i < 6; i++) {
                printf("\n");
            }

            printf("------------------------------\n");

            // --- MANO ---
            if (cs->fase == COMBAT_PLAYER_TURN) {
                printf(" MANO (%d):", cs->jugador.deck.mano_size);
                if (!cs->ya_robo_turno && !cs->carta_jugada_este_turno)
                    printf(" [X:Robar]");
                printf("\n");

                for (int i = 0; i < cs->jugador.deck.mano_size; i++) {
                    const CardData* c = cs->jugador.deck.mano[i];

                    if (i == cs->cursor) {
                        printf(">");
                    } else {
                        printf(" ");
                    }

                    printf("%s ", c->nombre);

                    // Iconos compactos
                    if (c->efectos & FX_ATTACK)     printf("A%d", c->ataque);
                    if (c->efectos & FX_SHIELD)     printf("E%d", c->escudo);
                    if (c->efectos & FX_HEAL)       printf("C%d", c->curacion);
                    if (c->efectos & FX_DRAW)       printf("R%d", c->robar);
                    if (c->efectos & FX_PLAY_AGAIN) printf("+");
                    printf("\n");
                }
            } else if (cs->fase == COMBAT_WIN) {
                printf("\n VICTORIA! START:Continuar\n");
            } else if (cs->fase == COMBAT_LOSE) {
                printf("\n DERROTA... START:Continuar\n");
            }
            break;
        }

        case GAME_RESULT:
            printf("\n\n\n\n");
            printf("   START: Menu Principal\n");
            break;
    }
}

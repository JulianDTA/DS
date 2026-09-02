#include "game.h"
#include "graphics.h"
#include <stdio.h>
#include <string.h>

// =====================================================
// ECUATRIALS - Flujo del Juego + Pantalla de Lore
// =====================================================

static const char* NOMBRES_PERSONAJES[] = {"Cantuna", "El Tin Tin", "La Tunda", "Padre Almeida", "Dama Tapada", "Maria Angula", "Gallo Catedral", "Cura sin Cabeza", "El Chuzalongo", "La Llorona", "Guagua Auca", "Viuda Tamarindo"};

static const CardData* get_deck_for_char(int id) {
    switch(id) {
        case 0: return CARTAS_CANTUNA;
        case 1: return CARTAS_TINTIN;
        case 2: return CARTAS_TUNDA;
        case 3: return CARTAS_ALMEIDA;
        case 4: return CARTAS_DAMATAPADA;
        case 5: return CARTAS_MARIANGULA;
        case 6: return CARTAS_GALLO;
        case 7: return CARTAS_CURA;
        case 8: return CARTAS_CHUZALONGO;
        case 9: return CARTAS_LLORONA;
        case 10: return CARTAS_GUAGUAAUCA;
        case 11: return CARTAS_VIUDA;
        default: return CARTAS_CANTUNA;
    }
}

static int get_deck_size_for_char(int id) {
    switch(id) {
        case 0: return CANTUNA_DECK_SIZE;
        case 1: return TINTIN_DECK_SIZE;
        case 2: return TUNDA_DECK_SIZE;
        case 3: return ALMEIDA_DECK_SIZE;
        case 4: return DAMATAPADA_DECK_SIZE;
        case 5: return MARIANGULA_DECK_SIZE;
        case 6: return GALLO_DECK_SIZE;
        case 7: return CURA_DECK_SIZE;
        case 8: return CHUZALONGO_DECK_SIZE;
        case 9: return LLORONA_DECK_SIZE;
        case 10: return GUAGUAAUCA_DECK_SIZE;
        case 11: return VIUDA_DECK_SIZE;
        default: return CANTUNA_DECK_SIZE;
    }
}

void game_init(GameState* gs) {
    // Saltar el menu y la seleccion directamente a combate para debugear graficos
    gs->fase = GAME_COMBAT;
    
    // Iniciar con personaje 0 vs personaje 1
    gs->personaje_elegido = 0;
    gs->rival_elegido = 1;
    combat_init(&gs->combate, 
        NOMBRES_PERSONAJES[0], get_deck_for_char(0), get_deck_size_for_char(0),
        NOMBRES_PERSONAJES[1], get_deck_for_char(1), get_deck_size_for_char(1));
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
                if (gs->personaje_elegido < 0) gs->personaje_elegido = 11;
            }
            if (keys_down & KEY_RIGHT) {
                gs->personaje_elegido++;
                if (gs->personaje_elegido > 11) gs->personaje_elegido = 0;
            }

            if (keys_down & KEY_A) {
                gs->rival_elegido = (gs->personaje_elegido + 1) % 12;

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
            combat_update(&gs->combate, keys_down, touch);

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
static void print_match_result(int winner, int loser, bool player_won) {
    printf("\n\n\n");
    if (player_won) {
        printf("   FELICIDADES!\n\n");
        printf("   %s ha vencido\n", NOMBRES_PERSONAJES[winner]);
        printf("   a %s!\n\n", NOMBRES_PERSONAJES[loser]);
    } else {
        printf("   HAS CAIDO...\n\n");
        printf("   %s fue derrotado\n", NOMBRES_PERSONAJES[loser]);
        printf("   por %s.\n\n", NOMBRES_PERSONAJES[winner]);
    }
    printf("   \"");
    if (winner == 0 && loser == 7) printf("%s", "El oro del diablo supera\n   a la magia oscura.");
    else if (winner == 8 && loser == 9) printf("%s", "El paramo no tiene\n   piedad de las lagrimas.");
    else if (winner == 9 && loser == 10) printf("%s", "Un bebe mas arrastrado\n   al fondo del rio...");
    else if (winner == 4 && loser == 1) printf("%s", "El seductor cayo\n   en la trampa mortal.");
    else if (winner == 3 && loser == 7) printf("%s", "Almeida seguira bebiendo;\n   el otro seguira penando.");
    else if (winner == 6 && loser == 0) printf("%s", "La Catedral impone\n   su ley sobre San Francisco.");
    else if (winner == 5 && loser == 9) printf("%s", "Tus llantos no callaran\n   mis gritos de culpa!");
    else if (winner == 10 && loser == 11) printf("%s", "Un demonio pequenito\n   gano a la tentacion.");
    else if (winner == 2 && loser == 5) printf("%s", "La nina traviesa termino\n   entundada en el manglar.");
    else if (winner == 11 && loser == 3) printf("%s", "La farra termino bajo\n   el arbol de tamarindo.");
    else if (winner == 0) printf("%s", "La arquitectura perfecta\n   nunca se derrumba.");
    else if (winner == 1) printf("%s", "Una travesura rapida\n   fue mas que suficiente.");
    else if (winner == 2) printf("%s", "Nadie escapa vivo de\n   los manglares...");
    else if (winner == 3) printf("%s", "Hasta la vuelta, senor!\n   Y a seguir bebiendo.");
    else if (winner == 4) printf("%s", "El terror absoluto\n   paralizo al oponente.");
    else if (winner == 5) printf("%s", "Devuelveme mis tripas!\n   La venganza esta servida.");
    else if (winner == 6) printf("%s", "Un canto de victoria\n   resuena en la plaza.");
    else if (winner == 7) printf("%s", "La magia de ultratumba\n   consumio su alma.");
    else if (winner == 8) printf("%s", "Fuerza bruta y salvaje\n   sin contemplaciones.");
    else if (winner == 9) printf("%s", "Tanto dolor y pena\n   terminan ahogando a todos.");
    else if (winner == 10) printf("%s", "Un llanto enganoso\n   termino en masacre.");
    else if (winner == 11) printf("%s", "Una trampa de la que\n   nunca despertara.");
    else printf("%s", "Victoria absoluta.");
    printf("\"\n\n\n");
    printf("   START: Menu Principal\n");
}

void game_draw_top(GameState* gs) {
    oamClear(&oamMain, 0, 128);
    
    if (gs->fase == GAME_COMBAT) {
        consoleSelect(topConsole);
        printf("\x1b[2J");
        
        printf("\x1b[11;3HHP: %d", gs->combate.jugador.hp);
        printf("\x1b[11;24HHP: %d", gs->combate.rival.hp);
        
        if (gfx_tunda) {
            // Jugador a la izquierda (Tunda)
            oamSet(&oamMain, 0, 10, 100, 0, 0, SpriteSize_64x64, SpriteColorFormat_256Color, 
                   gfx_tunda, -1, false, false, false, false, false);
        }
        if (gfx_cantuna) {
            // Rival a la derecha (Cantuna)
            oamSet(&oamMain, 1, 182, 100, 0, 0, SpriteSize_64x64, SpriteColorFormat_256Color, 
                   gfx_cantuna, -1, false, false, false, false, false);
        }
    }
}

#include "graphics.h"

void game_draw_bottom(GameState* gs) {
    // Limpiar OAM temporalmente
    oamClear(&oamSub, 0, 128);

    if (gs->fase == GAME_COMBAT) {
        CombatState* cs = &gs->combate;
        
        consoleSelect(subConsole);
        printf("\x1b[2J");
        
        if (cs->dragged_card_idx != -1) {
            const CardData* hover = cs->jugador.deck.mano[cs->dragged_card_idx];
            
            int len = 0;
            while(hover->nombre[len]) len++;
            
            // TITULO: Convertido a mayusculas para que simule ser mas grande
            char upper_name[64];
            for (int j = 0; j < len; j++) {
                if (hover->nombre[j] >= 'a' && hover->nombre[j] <= 'z') 
                    upper_name[j] = hover->nombre[j] - 32;
                else
                    upper_name[j] = hover->nombre[j];
            }
            upper_name[len] = '\0';
            printf("\x1b[5;%dH%s", 16 - len/2, upper_name);
            
            // ZONA AZUL: Lore a la izquierda (Columna 6, Fila 7 para subirlo un poco)
            if (hover->lore1) printf("\x1b[7;6H%s", hover->lore1);
            if (hover->lore2) printf("\x1b[8;6H%s", hover->lore2);
            if (hover->lore3) printf("\x1b[9;6H%s", hover->lore3);
            if (hover->lore4) printf("\x1b[10;6H%s", hover->lore4);
            if (hover->lore5) printf("\x1b[11;6H%s", hover->lore5);
            if (hover->lore6) printf("\x1b[12;6H%s", hover->lore6);
            if (hover->lore7) printf("\x1b[13;6H%s", hover->lore7);
            
            // ZONA VERDE/MORADA: Efecto a la derecha (Fila 7)
            printf("\x1b[7;21HEfecto:");
            if (hover->efectos & FX_ATTACK) {
                printf("\x1b[8;21HATQ: %d", hover->ataque);
            } else if (hover->efectos & FX_SHIELD) {
                printf("\x1b[8;21HDEF: %d", hover->escudo);
            } else if (hover->efectos & FX_HEAL) {
                printf("\x1b[8;21HCUR: %d", hover->curacion);
            } else if (hover->efectos & FX_AURA) {
                printf("\x1b[8;21HAURA");
            }
        } else {
            printf("\x1b[5;9H--- TABLERO ---");
            printf("\x1b[10;7HArrastra una carta");
            printf("\x1b[11;7Hpara leer su lore.");
        }
        
        // Poner Mazo debajo de la carta (Fila 23, Columna 23)
        printf("\x1b[23;23HMazo: %d", cs->jugador.deck.mazo_top); // Blanco para legibilidad
        
        // Dibujar el Mazo (esquina inferior derecha)
        if (gfx_card_gfx_mem) {
            oamSet(&oamSub, 0, 200, 110, 0, 0, SpriteSize_32x64, SpriteColorFormat_256Color, 
                   gfx_card_gfx_mem, -1, false, false, false, false, false);
        }

        // Dibujar las cartas en la mano
        for (int i = 0; i < cs->jugador.deck.mano_size; i++) {
            const CardData* c = cs->jugador.deck.mano[i];
            
            int x = i * 36 + 10;
            int y = 120;
            
            if (i == cs->dragged_card_idx) {
                x = cs->drag_x - 16;
                y = cs->drag_y - 32;
            }
            
            oamSet(&oamSub, i + 1, x, y, 0, 0, SpriteSize_32x64, SpriteColorFormat_256Color, 
                   gfx_card_gfx_mem, -1, false, false, false, false, false);
            
            int col = (x / 8) + 1;
            int row = (y / 8) + 1;
            if (col >= 1 && col <= 32 && row >= 1 && row <= 24) {
                // (Text overlay removed for now)
            }
        }
    }
}

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
    gs->fase = GAME_TITLE;
    gs->personaje_elegido = 0;
    gs->rival_elegido = 1;
    gs->top_dirty = true;
    gs->bottom_dirty = true;
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
                gs->top_dirty = true;
                gs->bottom_dirty = true;
            }
            break;

        case GAME_SELECT_CHAR:
            if (keys_down & KEY_LEFT) {
                gs->personaje_elegido--;
                if (gs->personaje_elegido < 0) gs->personaje_elegido = 11;
                gs->top_dirty = true;
                gs->bottom_dirty = true;
            }
            if (keys_down & KEY_RIGHT) {
                gs->personaje_elegido++;
                if (gs->personaje_elegido > 11) gs->personaje_elegido = 0;
                gs->top_dirty = true;
                gs->bottom_dirty = true;
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
                gs->top_dirty = true;
                gs->bottom_dirty = true;
            }

            if (keys_down & KEY_B) {
                gs->fase = GAME_TITLE;
                gs->top_dirty = true;
                gs->bottom_dirty = true;
            }
            break;

        case GAME_COMBAT:
            combat_update(&gs->combate, keys_down, touch);

            if (gs->combate.fase == COMBAT_WIN || gs->combate.fase == COMBAT_LOSE) {
                if (keys_down & KEY_START) {
                    gs->fase = GAME_RESULT;
                    gs->top_dirty = true;
                    gs->bottom_dirty = true;
                }
            }
            break;

        case GAME_RESULT:
            if (keys_down & KEY_START) {
                gs->fase = GAME_TITLE;
                gs->top_dirty = true;
                gs->bottom_dirty = true;
            }
            break;
    }
}

// =====================================================
// PANTALLA SUPERIOR: Descripcion y lore de la carta seleccionada
// =====================================================
static void print_match_result(int winner, int loser, bool player_won) {
    if (player_won) {
        printf("\x1b[3;4HFELICIDADES!");
        printf("\x1b[5;4H%s ha vencido", NOMBRES_PERSONAJES[winner]);
        printf("\x1b[6;4Ha %s!", NOMBRES_PERSONAJES[loser]);
    } else {
        printf("\x1b[3;4HHAS CAIDO...");
        printf("\x1b[5;4H%s fue derrotado", NOMBRES_PERSONAJES[loser]);
        printf("\x1b[6;4Hpor %s.", NOMBRES_PERSONAJES[winner]);
    }
    printf("\x1b[9;4H\"");
    
    // Line 9 and 10 for the quote
    if (winner == 0 && loser == 7) printf("\x1b[9;5HEl oro del diablo supera\x1b[10;5Ha la magia oscura.");
    else if (winner == 8 && loser == 9) printf("\x1b[9;5HEl paramo no tiene\x1b[10;5Hpiedad de las lagrimas.");
    else if (winner == 9 && loser == 10) printf("\x1b[9;5HUn bebe mas arrastrado\x1b[10;5Hal fondo del rio...");
    else if (winner == 4 && loser == 1) printf("\x1b[9;5HEl seductor cayo\x1b[10;5Hen la trampa mortal.");
    else if (winner == 3 && loser == 7) printf("\x1b[9;5HAlmeida seguira bebiendo;\x1b[10;5Hel otro seguira penando.");
    else if (winner == 6 && loser == 0) printf("\x1b[9;5HLa Catedral impone\x1b[10;5Hsu ley sobre San Francisco.");
    else if (winner == 5 && loser == 9) printf("\x1b[9;5HTus llantos no callaran\x1b[10;5Hmis gritos de culpa!");
    else if (winner == 10 && loser == 11) printf("\x1b[9;5HUn demonio pequenito\x1b[10;5Hgano a la tentacion.");
    else if (winner == 2 && loser == 5) printf("\x1b[9;5HLa nina traviesa termino\x1b[10;5Hentundada en el manglar.");
    else if (winner == 1 && loser == 8) printf("\x1b[9;5HEl duende robo el orgullo\x1b[10;5Hdel monstruo andino.");
    else if (winner == 7 && loser == 4) printf("\x1b[9;5HNi tu perfume apagara\x1b[10;5Hlas llamas del infierno.");
    else if (winner == 11 && loser == 3) printf("\x1b[9;5HVen, padrecito, acercate\x1b[10;5Hal tamarindo...");
    else printf("\x1b[9;5HEl destino favorece\x1b[10;5Hal vencedor hoy.");
    printf("\"");
}

void game_draw_top(GameState* gs) {
    if (gs->fase != GAME_COMBAT && !gs->top_dirty) return;
    gs->top_dirty = false;

    oamClear(&oamMain, 0, 128);
    consoleSelect(topConsole);
    printf("\x1b[2J");
    
    if (gs->fase == GAME_TITLE) {
        printf("\x1b[32m\x1b[4;8HECUATRIALS\n");
        printf("\x1b[6;5HPulsa START para jugar\x1b[39m\n");
    } else if (gs->fase == GAME_SELECT_CHAR) {
        printf("\x1b[32m\x1b[2;5HSELECCION DE PERSONAJE\n");
        printf("\x1b[5;10H%s\n", NOMBRES_PERSONAJES[gs->personaje_elegido]);
        printf("\x1b[21;5HPulsa A para confirmar\n");
        printf("\x1b[22;5HPulsa B para volver\x1b[39m\n");
    } else if (gs->fase == GAME_RESULT) {
        printf("\x1b[32m\x1b[4;8HFIN DEL COMBATE\n");
        printf("\x1b[6;5HPulsa START para salir\x1b[39m\n");
    } else if (gs->fase == GAME_COMBAT) {
        // Player (Left) - moved to bottom of top screen
        printf("\x1b[32m\x1b[21;1H%s", gs->combate.jugador.nombre);
        printf("\x1b[22;1HHP: %d/%d", gs->combate.jugador.hp, gs->combate.jugador.max_hp);
        printf("\x1b[23;1HDEF: %d", deck_get_total_shield(&gs->combate.jugador.deck));
        
        // Rival (Right) - moved to bottom of top screen
        printf("\x1b[21;18H%s", gs->combate.rival.nombre);
        printf("\x1b[22;18HHP: %d/%d", gs->combate.rival.hp, gs->combate.rival.max_hp);
        printf("\x1b[23;18HDEF: %d\x1b[39m", deck_get_total_shield(&gs->combate.rival.deck));
        
        // Combat Log (Center Top, Rows 2-7) stays in the sky!
        for (int i = 0; i < gs->combate.log_count; i++) {
            char* msg = gs->combate.log[i];
            int len = 0; while (msg[len]) len++;
            int col = (32 - len) / 2;
            if (col < 1) col = 1;
            printf("\x1b[%d;%dH\x1b[32m%s\x1b[39m", i + 12, col, msg);
        }

        u16* p_gfx = (gs->personaje_elegido == 2) ? gfx_tunda : gfx_cantuna;
        int p_pal = (gs->personaje_elegido == 2) ? 1 : 0;
        u16* r_gfx = (gs->rival_elegido == 2) ? gfx_tunda : gfx_cantuna;
        int r_pal = (gs->rival_elegido == 2) ? 1 : 0;
        
        if (p_gfx) {
            oamSet(&oamMain, 0, 10, 100, 0, p_pal, SpriteSize_64x64, SpriteColorFormat_256Color, 
                   p_gfx, -1, false, false, true, false, false);
        }
        if (r_gfx) {
            oamSet(&oamMain, 1, 182, 100, 0, r_pal, SpriteSize_64x64, SpriteColorFormat_256Color, 
                   r_gfx, -1, false, false, false, false, false);
        }
    }
}

#include "graphics.h"

void game_draw_bottom(GameState* gs) {
    if (gs->fase != GAME_COMBAT && !gs->bottom_dirty) return;
    gs->bottom_dirty = false;

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
            if (hover->lore1) printf("\x1b[7;3H%s", hover->lore1);
            if (hover->lore2) printf("\x1b[8;3H%s", hover->lore2);
            if (hover->lore3) printf("\x1b[9;3H%s", hover->lore3);
            if (hover->lore4) printf("\x1b[10;3H%s", hover->lore4);
            if (hover->lore5) printf("\x1b[11;3H%s", hover->lore5);
            if (hover->lore6) printf("\x1b[12;3H%s", hover->lore6);
            if (hover->lore7) printf("\x1b[13;3H%s", hover->lore7);
            
            // ZONA VERDE/MORADA: Efecto a la derecha (Fila 7)
            printf("\x1b[7;21HEfecto:");
            int ey = 8;
            if (hover->efectos & FX_ATTACK) printf("\x1b[%d;21HATQ: %d", ey++, hover->ataque);
            if (hover->efectos & FX_SHIELD) printf("\x1b[%d;21HDEF: %d", ey++, hover->escudo);
            if (hover->efectos & FX_HEAL) printf("\x1b[%d;21HCUR: %d", ey++, hover->curacion);
            if (hover->efectos & FX_DRAW) printf("\x1b[%d;21HRoba %d", ey++, hover->robar);
            if (hover->efectos & FX_STEAL_HAND) printf("\x1b[%d;21HRoba Mano", ey++);
            if (hover->efectos & FX_STEAL_DECK) printf("\x1b[%d;21HRoba Mazo", ey++);
            if (hover->efectos & FX_STEAL_DISCARD) printf("\x1b[%d;21HRoba Cem", ey++);
            if (hover->efectos & FX_PLAY_AGAIN) printf("\x1b[%d;21H+Juega", ey++);
            if (hover->efectos & FX_AURA) printf("\x1b[%d;21HAURA", ey++);
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
            
            int x = get_card_x(i, cs->jugador.deck.mano_size);
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
    } else if (gs->fase == GAME_TITLE) {
        consoleSelect(subConsole);
        printf("\x1b[2J");
        printf("\x1b[5;4HBATALLAS MITOLOGICAS");
        printf("\x1b[6;4HDEL ECUADOR");
        printf("\x1b[9;4HPresiona START en la");
        printf("\x1b[10;4Hpantalla superior.");
    } else if (gs->fase == GAME_SELECT_CHAR) {
        consoleSelect(subConsole);
        printf("\x1b[2J");
        switch (gs->personaje_elegido) {
        case 0:
            printf("\x1b[3;4H%s\n\n", NOMBRES_PERSONAJES[0]);
            printf("\x1b[5;3HCuenta la leyenda que");
            printf("\x1b[6;3HCantuna hizo un pacto con");
            printf("\x1b[7;3Hel diablo para construir");
            printf("\x1b[8;3Hla Iglesia de San Francisco");
            printf("\x1b[9;3Hen una sola noche.");
            printf("\x1b[10;3H");
            printf("\x1b[11;3HPero el astuto constructor");
            printf("\x1b[12;3Hquito un ladrillo antes de");
            printf("\x1b[13;3Hamanecer, y el diablo no");
            printf("\x1b[14;3Hpudo reclamar su alma.");
            printf("\x1b[15;3H");
            printf("\x1b[16;3HRol: TANQUE");
            printf("\x1b[17;3HEscudos fuertes, golpes");
            printf("\x1b[18;3Hdevastadores.");
            break;
        case 1:
            printf("\x1b[3;4H%s\n\n", NOMBRES_PERSONAJES[1]);
            printf("\x1b[5;3HUn duende travieso de la");
            printf("\x1b[6;3Hcosta ecuatoriana.");
            printf("\x1b[7;3HUsa un sombrero enorme y");
            printf("\x1b[8;3Haparece en las sombras");
            printf("\x1b[9;3Hpara asustar a la gente.");
            printf("\x1b[10;3H");
            printf("\x1b[11;3HLe encanta esconder cosas,");
            printf("\x1b[12;3Hhacer nudos en el cabello");
            printf("\x1b[13;3Hy robar de los bolsillos");
            printf("\x1b[14;3Hcon sus manos rapidas.");
            printf("\x1b[15;3H");
            printf("\x1b[16;3HRol: AGRESOR");
            printf("\x1b[17;3HAtaques rapidos, combos");
            printf("\x1b[18;3Himpredecibles.");
            break;
        case 2:
            printf("\x1b[3;4H%s\n\n", NOMBRES_PERSONAJES[2]);
            printf("\x1b[5;3HEspiritu del manglar.");
            printf("\x1b[6;3HTiene una pierna humana");
            printf("\x1b[7;3Hy otra de molinillo.");
            printf("\x1b[8;3H");
            printf("\x1b[9;3HSe disfraza de un ser");
            printf("\x1b[10;3Hquerido para atraer a");
            printf("\x1b[11;3Hlos ninos al bosque");
            printf("\x1b[12;3Hofreciendo camarones.");
            printf("\x1b[13;3HAsi los hipnotiza.");
            printf("\x1b[14;3H");
            printf("\x1b[15;3HRol: CONTROL");
            printf("\x1b[16;3HCuracion poderosa y");
            printf("\x1b[17;3Hdrenaje de vida.");
            break;
        case 3:
            printf("\x1b[3;4H%s\n\n", NOMBRES_PERSONAJES[3]);
            printf("\x1b[5;3HUn sacerdote franciscano");
            printf("\x1b[6;3Hque escapaba del convento");
            printf("\x1b[7;3Hpara irse de farra.");
            printf("\x1b[8;3H");
            printf("\x1b[9;3HPisaba la estatua de");
            printf("\x1b[10;3HCristo, quien le pregunto:");
            printf("\x1b[11;3HHasta cuando Padre");
            printf("\x1b[12;3HAlmeida? El respondio:");
            printf("\x1b[13;3HHasta la vuelta, Senor.");
            printf("\x1b[14;3H");
            printf("\x1b[15;3HRol: COMBO");
            printf("\x1b[16;3HPoca defensa pero");
            printf("\x1b[17;3Hmucho robo de cartas.");
            break;
        case 4:
            printf("\x1b[3;4H%s\n\n", NOMBRES_PERSONAJES[4]);
            printf("\x1b[5;3HMisteriosa mujer que");
            printf("\x1b[6;3Hcamina por Guayaquil a");
            printf("\x1b[7;3Hla medianoche.");
            printf("\x1b[8;3HSu perfume embriagador");
            printf("\x1b[9;3Hatrae a los hombres.");
            printf("\x1b[10;3H");
            printf("\x1b[11;3HAl quitarse el velo,");
            printf("\x1b[12;3Hmuestra su craneo y");
            printf("\x1b[13;3Hun olor a muerte que");
            printf("\x1b[14;3Hparaliza a sus victimas.");
            printf("\x1b[15;3H");
            printf("\x1b[16;3HRol: TERROR");
            printf("\x1b[17;3HDebuffs, escudos y");
            printf("\x1b[18;3Hdano masivo.");
            break;
        case 5:
            printf("\x1b[3;4H%s\n\n", NOMBRES_PERSONAJES[5]);
            printf("\x1b[5;3HNina muy golosa.");
            printf("\x1b[6;3HSu madre le pidio");
            printf("\x1b[7;3Hcomprar tripas, pero");
            printf("\x1b[8;3Hse gasto el dinero.");
            printf("\x1b[9;3H");
            printf("\x1b[10;3HPara enganarla, robo");
            printf("\x1b[11;3Hlas tripas de un muerto.");
            printf("\x1b[12;3HEl espiritu la busco");
            printf("\x1b[13;3Hgritando por sus tripas.");
            printf("\x1b[14;3H");
            printf("\x1b[15;3HRol: AGRESOR");
            printf("\x1b[16;3HAtaques freneticos y");
            printf("\x1b[17;3Hcomportamiento salvaje.");
            break;
        case 6:
            printf("\x1b[3;4H%s\n\n", NOMBRES_PERSONAJES[6]);
            printf("\x1b[5;3HEl gallo de bronce de");
            printf("\x1b[6;3Hla Catedral cobro vida");
            printf("\x1b[7;3Hpara darle una leccion");
            printf("\x1b[8;3Ha Don Ramon Ayala,");
            printf("\x1b[9;3Hun hombre jactancioso.");
            printf("\x1b[10;3H");
            printf("\x1b[11;3HDespues de que lo");
            printf("\x1b[12;3Hinsultara repetidas veces,");
            printf("\x1b[13;3Hel ave dorada bajo a");
            printf("\x1b[14;3Hpicotearlo sin piedad.");
            printf("\x1b[15;3H");
            printf("\x1b[16;3HRol: EQUILIBRADO");
            printf("\x1b[17;3HAtaques desde el aire,");
            printf("\x1b[18;3Hbuena curacion.");
            break;
        case 7:
            printf("\x1b[3;4H%s\n\n", NOMBRES_PERSONAJES[7]);
            printf("\x1b[5;3HEl espectro de un");
            printf("\x1b[6;3Hsacerdote condenado");
            printf("\x1b[7;3Ha vagar sin su cabeza");
            printf("\x1b[8;3Hpor sus terribles pecados.");
            printf("\x1b[9;3H");
            printf("\x1b[10;3HSu silueta oscura");
            printf("\x1b[11;3Hatormenta las calles,");
            printf("\x1b[12;3Hemanando un frio");
            printf("\x1b[13;3Hsobrenatural a su paso.");
            printf("\x1b[14;3H");
            printf("\x1b[15;3HRol: MAGIA");
            printf("\x1b[16;3HDano magico norme,");
            printf("\x1b[17;3Himposible de bloquear.");
            break;
        case 8:
            printf("\x1b[3;4H%s\n\n", NOMBRES_PERSONAJES[8]);
            printf("\x1b[5;3HUna criatura salvaje");
            printf("\x1b[6;3Hde los paramos andinos.");
            printf("\x1b[7;3HMitad nino, mitad bestia,");
            printf("\x1b[8;3Hprotege a los animales.");
            printf("\x1b[9;3H");
            printf("\x1b[10;3HTiene una agresividad");
            printf("\x1b[11;3Hdesmedida y ataca con");
            printf("\x1b[12;3Hfuria incontrolable a");
            printf("\x1b[13;3Hquien falte el respeto.");
            printf("\x1b[14;3H");
            printf("\x1b[15;3HRol: SALVAJE");
            printf("\x1b[16;3HAtaques brutales puros");
            printf("\x1b[17;3Hcon nula defensa.");
            break;
        case 9:
            printf("\x1b[3;4H%s\n\n", NOMBRES_PERSONAJES[9]);
            printf("\x1b[5;3HEl alma en pena de");
            printf("\x1b[6;3Huna mujer que perdio a");
            printf("\x1b[7;3Hsu hijo en un rio.");
            printf("\x1b[8;3H");
            printf("\x1b[9;3HVaga por las orillas");
            printf("\x1b[10;3Hllorando sin consuelo.");
            printf("\x1b[11;3HSu inmenso dolor");
            printf("\x1b[12;3Hmarchita las plantas y");
            printf("\x1b[13;3Hhiela la sangre.");
            printf("\x1b[14;3H");
            printf("\x1b[15;3HRol: TRISTEZA");
            printf("\x1b[16;3HMucha curacion base y");
            printf("\x1b[17;3Hescudos impenetrables.");
            break;
        case 10:
            printf("\x1b[3;4H%s\n\n", NOMBRES_PERSONAJES[10]);
            printf("\x1b[5;3HEl espiritu de un bebe");
            printf("\x1b[6;3Hno bautizado que fue");
            printf("\x1b[7;3Habandonado. Su llanto");
            printf("\x1b[8;3Hdespierta compasion.");
            printf("\x1b[9;3H");
            printf("\x1b[10;3HPero cuando un viajero");
            printf("\x1b[11;3Hlo toma en sus brazos,");
            printf("\x1b[12;3Hel bebe muestra dientes");
            printf("\x1b[13;3Hde demonio y ataca.");
            printf("\x1b[14;3H");
            printf("\x1b[15;3HRol: SORPRESA");
            printf("\x1b[16;3HRobo de cartas");
            printf("\x1b[17;3Hy ataques enganosos.");
            break;
        case 11:
            printf("\x1b[3;4H%s\n\n", NOMBRES_PERSONAJES[11]);
            printf("\x1b[5;3HEl fantasma de una");
            printf("\x1b[6;3Hmujer que ronda un");
            printf("\x1b[7;3Hantiguo tamarindo.");
            printf("\x1b[8;3H");
            printf("\x1b[9;3HLlora buscando consuelo,");
            printf("\x1b[10;3Hpero si alguien se le");
            printf("\x1b[11;3Hacerca, revela un rostro");
            printf("\x1b[12;3Hque provoca la locura.");
            printf("\x1b[13;3H");
            printf("\x1b[14;3HRol: TRAMPA");
            printf("\x1b[15;3HDrenaje de vida,");
            printf("\x1b[16;3Hilusiones y control.");
            break;
        }
    } else if (gs->fase == GAME_RESULT) {
        consoleSelect(subConsole);
        printf("\x1b[2J");
        int winner = (gs->combate.jugador.hp > 0) ? gs->personaje_elegido : gs->rival_elegido;
        int loser = (gs->combate.jugador.hp > 0) ? gs->rival_elegido : gs->personaje_elegido;
        bool pwon = (gs->combate.jugador.hp > 0);
        print_match_result(winner, loser, pwon);
    }
}

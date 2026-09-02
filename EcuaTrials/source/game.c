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
    consoleSelect(topConsole);
    printf("\x1b[2J");
    
    if (gs->fase == GAME_TITLE) {
        printf("\x1b[10;8HECUATRIALS\n");
        printf("\x1b[12;5HPulsa START para jugar\n");
    } else if (gs->fase == GAME_SELECT_CHAR) {
        printf("\x1b[10;5HSELECCION DE PERSONAJE\n");
        printf("\x1b[12;8H%s\n", NOMBRES_PERSONAJES[gs->personaje_elegido]);
        printf("\x1b[14;5HPulsa A para confirmar\n");
        printf("\x1b[16;5HPulsa B para volver\n");
    } else if (gs->fase == GAME_RESULT) {
        printf("\x1b[10;8HFIN DEL COMBATE\n");
        printf("\x1b[12;5HPulsa START para salir\n");
    } else if (gs->fase == GAME_COMBAT) {
        // Player (Left)
        printf("\x1b[10;1H%s", gs->combate.jugador.nombre);
        printf("\x1b[11;1HHP: %d/%d", gs->combate.jugador.hp, gs->combate.jugador.max_hp);
        printf("\x1b[12;1HDEF: %d", deck_get_total_shield(&gs->combate.jugador.deck));
        
        // Rival (Right)
        printf("\x1b[10;18H%s", gs->combate.rival.nombre);
        printf("\x1b[11;18HHP: %d/%d", gs->combate.rival.hp, gs->combate.rival.max_hp);
        printf("\x1b[12;18HDEF: %d", deck_get_total_shield(&gs->combate.rival.deck));
        
        // Combat Log (Center Top, Rows 2-7)
        for (int i = 0; i < gs->combate.log_count; i++) {
            char* msg = gs->combate.log[i];
            int len = 0; while (msg[len]) len++;
            int col = (32 - len) / 2;
            if (col < 1) col = 1;
            printf("\x1b[%d;%dH%s", i + 2, col, msg);
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
        printf("\n\n\n\n\n   BATALLAS MITOLOGICAS\n   DEL ECUADOR\n\n   Presiona START en la\n   pantalla superior.");
    } else if (gs->fase == GAME_SELECT_CHAR) {
        consoleSelect(subConsole);
        printf("\x1b[2J");
        printf("\n\n");
        switch (gs->personaje_elegido) {
case 0:
    printf("   ========================\n");
    printf("   %s\n", NOMBRES_PERSONAJES[0]);
    printf("   ========================\n\n");
    printf("   Cuenta la leyenda que\n");
    printf("   Cantuna hizo un pacto con\n");
    printf("   el diablo para construir\n");
    printf("   la Iglesia de San Francisco\n");
    printf("   en una sola noche.\n");
    printf("   \n");
    printf("   Pero el astuto constructor\n");
    printf("   quito un ladrillo antes de\n");
    printf("   amanecer, y el diablo no\n");
    printf("   pudo reclamar su alma.\n");
    printf("   \n");
    printf("   Rol: TANQUE\n");
    printf("   Escudos fuertes, golpes\n");
    printf("   devastadores.\n");
    break;
case 1:
    printf("   ========================\n");
    printf("   %s\n", NOMBRES_PERSONAJES[1]);
    printf("   ========================\n\n");
    printf("   Un duende travieso de la\n");
    printf("   costa ecuatoriana.\n");
    printf("   Usa un sombrero enorme y\n");
    printf("   aparece en las sombras\n");
    printf("   para asustar a la gente.\n");
    printf("   \n");
    printf("   Le encanta esconder cosas,\n");
    printf("   hacer nudos en el cabello\n");
    printf("   y robar de los bolsillos\n");
    printf("   con sus manos rapidas.\n");
    printf("   \n");
    printf("   Rol: AGRESOR\n");
    printf("   Ataques rapidos, combos\n");
    printf("   impredecibles.\n");
    break;
case 2:
    printf("   ========================\n");
    printf("   %s\n", NOMBRES_PERSONAJES[2]);
    printf("   ========================\n\n");
    printf("   Espiritu del manglar.\n");
    printf("   Tiene una pierna humana\n");
    printf("   y otra de molinillo.\n");
    printf("   \n");
    printf("   Se disfraza de un ser\n");
    printf("   querido para atraer a\n");
    printf("   los ninos al bosque\n");
    printf("   ofreciendo camarones.\n");
    printf("   Asi los hipnotiza.\n");
    printf("   \n");
    printf("   Rol: CONTROL\n");
    printf("   Curacion poderosa y\n");
    printf("   drenaje de vida.\n");
    break;
case 3:
    printf("   ========================\n");
    printf("   %s\n", NOMBRES_PERSONAJES[3]);
    printf("   ========================\n\n");
    printf("   Un sacerdote franciscano\n");
    printf("   que escapaba del convento\n");
    printf("   para irse de farra.\n");
    printf("   \n");
    printf("   Pisaba la estatua de\n");
    printf("   Cristo, quien le pregunto:\n");
    printf("   Hasta cuando Padre\n");
    printf("   Almeida? El respondio:\n");
    printf("   Hasta la vuelta, Senor.\n");
    printf("   \n");
    printf("   Rol: COMBO\n");
    printf("   Poca defensa pero\n");
    printf("   mucho robo de cartas.\n");
    break;
case 4:
    printf("   ========================\n");
    printf("   %s\n", NOMBRES_PERSONAJES[4]);
    printf("   ========================\n\n");
    printf("   Misteriosa mujer que\n");
    printf("   camina por Guayaquil a\n");
    printf("   la medianoche.\n");
    printf("   Su perfume embriagador\n");
    printf("   atrae a los hombres.\n");
    printf("   \n");
    printf("   Al quitarse el velo,\n");
    printf("   muestra su craneo y\n");
    printf("   un olor a muerte que\n");
    printf("   paraliza a sus victimas.\n");
    printf("   \n");
    printf("   Rol: TERROR\n");
    printf("   Debuffs, escudos y\n");
    printf("   dano masivo.\n");
    break;
case 5:
    printf("   ========================\n");
    printf("   %s\n", NOMBRES_PERSONAJES[5]);
    printf("   ========================\n\n");
    printf("   Nina muy golosa.\n");
    printf("   Su madre le pidio\n");
    printf("   comprar tripas, pero\n");
    printf("   se gasto el dinero.\n");
    printf("   \n");
    printf("   Para enganarla, robo\n");
    printf("   las tripas de un muerto.\n");
    printf("   El espiritu la busco\n");
    printf("   gritando por sus tripas.\n");
    printf("   \n");
    printf("   Rol: AGRESOR\n");
    printf("   Ataques freneticos y\n");
    printf("   comportamiento salvaje.\n");
    break;
case 6:
    printf("   ========================\n");
    printf("   %s\n", NOMBRES_PERSONAJES[6]);
    printf("   ========================\n\n");
    printf("   El gallo de bronce de\n");
    printf("   la Catedral cobro vida\n");
    printf("   para darle una leccion\n");
    printf("   a Don Ramon Ayala,\n");
    printf("   un hombre jactancioso.\n");
    printf("   \n");
    printf("   Despues de que lo\n");
    printf("   insultara repetidas veces,\n");
    printf("   el ave dorada bajo a\n");
    printf("   picotearlo sin piedad.\n");
    printf("   \n");
    printf("   Rol: EQUILIBRADO\n");
    printf("   Ataques desde el aire,\n");
    printf("   buena curacion.\n");
    break;
case 7:
    printf("   ========================\n");
    printf("   %s\n", NOMBRES_PERSONAJES[7]);
    printf("   ========================\n\n");
    printf("   El espectro de un\n");
    printf("   sacerdote condenado\n");
    printf("   a vagar sin su cabeza\n");
    printf("   por sus terribles pecados.\n");
    printf("   \n");
    printf("   Su silueta oscura\n");
    printf("   atormenta las calles,\n");
    printf("   emanando un frio\n");
    printf("   sobrenatural a su paso.\n");
    printf("   \n");
    printf("   Rol: MAGIA\n");
    printf("   Dano magico norme,\n");
    printf("   imposible de bloquear.\n");
    break;
case 8:
    printf("   ========================\n");
    printf("   %s\n", NOMBRES_PERSONAJES[8]);
    printf("   ========================\n\n");
    printf("   Una criatura salvaje\n");
    printf("   de los paramos andinos.\n");
    printf("   Mitad nino, mitad bestia,\n");
    printf("   protege a los animales.\n");
    printf("   \n");
    printf("   Tiene una agresividad\n");
    printf("   desmedida y ataca con\n");
    printf("   furia incontrolable a\n");
    printf("   quien falte el respeto.\n");
    printf("   \n");
    printf("   Rol: SALVAJE\n");
    printf("   Ataques brutales puros\n");
    printf("   con nula defensa.\n");
    break;
case 9:
    printf("   ========================\n");
    printf("   %s\n", NOMBRES_PERSONAJES[9]);
    printf("   ========================\n\n");
    printf("   El alma en pena de\n");
    printf("   una mujer que perdio a\n");
    printf("   su hijo en un rio.\n");
    printf("   \n");
    printf("   Vaga por las orillas\n");
    printf("   llorando sin consuelo.\n");
    printf("   Su inmenso dolor\n");
    printf("   marchita las plantas y\n");
    printf("   hiela la sangre.\n");
    printf("   \n");
    printf("   Rol: TRISTEZA\n");
    printf("   Mucha curacion base y\n");
    printf("   escudos impenetrables.\n");
    break;
case 10:
    printf("   ========================\n");
    printf("   %s\n", NOMBRES_PERSONAJES[10]);
    printf("   ========================\n\n");
    printf("   El espiritu de un bebe\n");
    printf("   no bautizado que fue\n");
    printf("   abandonado. Su llanto\n");
    printf("   despierta compasion.\n");
    printf("   \n");
    printf("   Pero cuando un viajero\n");
    printf("   lo toma en sus brazos,\n");
    printf("   el bebe muestra dientes\n");
    printf("   de demonio y ataca.\n");
    printf("   \n");
    printf("   Rol: SORPRESA\n");
    printf("   Robo de cartas\n");
    printf("   y ataques enganosos.\n");
    break;
case 11:
    printf("   ========================\n");
    printf("   %s\n", NOMBRES_PERSONAJES[11]);
    printf("   ========================\n\n");
    printf("   El fantasma de una\n");
    printf("   mujer que ronda un\n");
    printf("   antiguo tamarindo.\n");
    printf("   \n");
    printf("   Llora buscando consuelo,\n");
    printf("   pero si alguien se le\n");
    printf("   acerca, revela un rostro\n");
    printf("   que provoca la locura.\n");
    printf("   \n");
    printf("   Rol: TRAMPA\n");
    printf("   Drenaje de vida,\n");
    printf("   ilusiones y control.\n");
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

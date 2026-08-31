#include "game.h"
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
            printf("    \n");
            printf("    \n\n");
            printf("    v0.2 - 2026\n");
            break;

        case GAME_SELECT_CHAR:
            printf("\n\n");
            switch (gs->personaje_elegido) {
case 0:
    printf("   ========================\n");
    printf("   %s\n", NOMBRES_PERSONAJES[0]);
    printf("   ========================\n\n");
    printf("  Cuenta la leyenda que Cantuna\n");
    printf("  hizo un pacto con el diablo para\n");
    printf("  construir la Iglesia de San\n");
    printf("  Francisco en Quito en una sola\n");
    printf("  noche.\n");
    printf("   \n");
    printf("  Pero el astuto constructor\n");
    printf("  quito un ladrillo antes del\n");
    printf("  amanecer, y el diablo no pudo\n");
    printf("  reclamar su alma.\n");
    printf("   \n");
    printf("  Rol: TANQUE\n");
    printf("  Escudos fuertes, golpes\n");
    printf("  devastadores.\n");
    break;
case 1:
    printf("   ========================\n");
    printf("   %s\n", NOMBRES_PERSONAJES[1]);
    printf("   ========================\n\n");
    printf("  Un duende travieso y escurridizo\n");
    printf("  de la costa ecuatoriana.\n");
    printf("  Usa un sombrero enorme y\n");
    printf("  aparece en los caminos oscuros\n");
    printf("  para asustar a los viajeros.\n");
    printf("   \n");
    printf("  Le encanta esconder cosas,\n");
    printf("  hacer nudos en el cabello y\n");
    printf("  robar de los bolsillos con\n");
    printf("  sus manos rapidisimas.\n");
    printf("   \n");
    printf("  Rol: AGRESOR\n");
    printf("  Ataques rapidos, cadenas\n");
    printf("  de combos impredecibles.\n");
    break;
case 2:
    printf("   ========================\n");
    printf("   %s\n", NOMBRES_PERSONAJES[2]);
    printf("   ========================\n\n");
    printf("  Espiritu femenino de los\n");
    printf("  manglares de Esmeraldas.\n");
    printf("  Tiene una pierna humana y\n");
    printf("  otra de molinillo de madera.\n");
    printf("   \n");
    printf("  Se transforma en un ser\n");
    printf("  querido para atraer a los\n");
    printf("  ninos al bosque ofreciendoles\n");
    printf("  camarones magicos, donde los\n");
    printf("  hipnotiza ('entunda').\n");
    printf("   \n");
    printf("  Rol: CONTROL\n");
    printf("  Curacion poderosa y\n");
    printf("  drenaje de vida.\n");
    break;
case 3:
    printf("   ========================\n");
    printf("   %s\n", NOMBRES_PERSONAJES[3]);
    printf("   ========================\n\n");
    printf("  Un sacerdote franciscano\n");
    printf("  de Quito que escapaba de su\n");
    printf("  convento por las noches para\n");
    printf("  irse de farra y beber.\n");
    printf("   \n");
    printf("  Para salir, pisaba la estatua\n");
    printf("  de Cristo, quien un dia le\n");
    printf("  pregunto: 'Hasta cuando Padre\n");
    printf("  Almeida?'. El respondio:\n");
    printf("  'Hasta la vuelta, Senor'.\n");
    printf("   \n");
    printf("  Rol: COMBO\n");
    printf("  Poca defensa pero\n");
    printf("  mucho robo de cartas.\n");
    break;
case 4:
    printf("   ========================\n");
    printf("   %s\n", NOMBRES_PERSONAJES[4]);
    printf("   ========================\n\n");
    printf("  Una misteriosa mujer que\n");
    printf("  camina por las calles de\n");
    printf("  Guayaquil pasada la medianoche.\n");
    printf("  Exhala un perfume embriagador\n");
    printf("  que atrae a los hombres.\n");
    printf("   \n");
    printf("  Al descubrirse el velo,\n");
    printf("  muestra un rostro calaverico\n");
    printf("  y un olor a muerte que paraliza\n");
    printf("  de terror a sus victimas.\n");
    printf("   \n");
    printf("  Rol: TERROR\n");
    printf("  Debuffs, escudos espectrales\n");
    printf("  y dano masivo.\n");
    break;
case 5:
    printf("   ========================\n");
    printf("   %s\n", NOMBRES_PERSONAJES[5]);
    printf("   ========================\n\n");
    printf("  Una nina muy golosa y\n");
    printf("  mentirosa. Su madre le pidio\n");
    printf("  comprar tripas, pero ella se\n");
    printf("  gasto el dinero en dulces.\n");
    printf("   \n");
    printf("  Para enganarla, robo las\n");
    printf("  tripas de un muerto fresco.\n");
    printf("  Esa noche, el espiritu\n");
    printf("  fue a buscarla gritando:\n");
    printf("  'Devuelveme mis tripas!'\n");
    printf("   \n");
    printf("  Rol: AGRESOR\n");
    printf("  Ataques freneticos y\n");
    printf("  comportamiento salvaje.\n");
    break;
case 6:
    printf("   ========================\n");
    printf("   %s\n", NOMBRES_PERSONAJES[6]);
    printf("   ========================\n\n");
    printf("  El gallo de bronce de la\n");
    printf("  Catedral de Quito cobro vida\n");
    printf("  para darle una leccion a Don\n");
    printf("  Ramon Ayala, un hombre rico\n");
    printf("  y muy jactancioso.\n");
    printf("   \n");
    printf("  Despues de que Don Ramon\n");
    printf("  insultara al gallo repetidas\n");
    printf("  veces, el ave dorada bajo\n");
    printf("  a picotearlo sin piedad.\n");
    printf("   \n");
    printf("  Rol: EQUILIBRADO\n");
    printf("  Ataques desde el aire,\n");
    printf("  buena curacion.\n");
    break;
case 7:
    printf("   ========================\n");
    printf("   %s\n", NOMBRES_PERSONAJES[7]);
    printf("   ========================\n\n");
    printf("  El espectro de un sacerdote\n");
    printf("  condenado a vagar sin su\n");
    printf("  cabeza por sus terribles\n");
    printf("  pecados en vida.\n");
    printf("   \n");
    printf("  Su silueta oscura atormenta\n");
    printf("  las calles empedradas de la\n");
    printf("  sierra, emanando un frio\n");
    printf("  sobrenatural a su paso.\n");
    printf("   \n");
    printf("  Rol: MAGIA\n");
    printf("  Dano magico enorme,\n");
    printf("  imposible de bloquear\n");
    printf("  con escudos fisicos.\n");
    break;
case 8:
    printf("   ========================\n");
    printf("   %s\n", NOMBRES_PERSONAJES[8]);
    printf("   ========================\n\n");
    printf("  Una criatura salvaje de\n");
    printf("  los paramos andinos.\n");
    printf("  Mitad nino, mitad bestia,\n");
    printf("  protege celosamente a los\n");
    printf("  animales salvajes.\n");
    printf("   \n");
    printf("  Tiene una agresividad\n");
    printf("  desmedida y ataca con una\n");
    printf("  furia incontrolable a quien\n");
    printf("  falte el respeto a su hogar.\n");
    printf("   \n");
    printf("  Rol: SALVAJE\n");
    printf("  Ataques brutales puros\n");
    printf("  con nula defensa.\n");
    break;
case 9:
    printf("   ========================\n");
    printf("   %s\n", NOMBRES_PERSONAJES[9]);
    printf("   ========================\n\n");
    printf("  El alma en pena de una\n");
    printf("  mujer que perdio a su hijo\n");
    printf("  en las aguas de un rio.\n");
    printf("   \n");
    printf("  Vaga por las orillas llorando\n");
    printf("  desconsoladamente. Su dolor\n");
    printf("  es tan grande que marchita\n");
    printf("  las plantas y hiela la sangre\n");
    printf("  de quien la escucha.\n");
    printf("   \n");
    printf("  Rol: TRISTEZA\n");
    printf("  Mucha curacion base y\n");
    printf("  escudos impenetrables.\n");
    break;
case 10:
    printf("   ========================\n");
    printf("   %s\n", NOMBRES_PERSONAJES[10]);
    printf("   ========================\n\n");
    printf("  El espiritu de un bebe\n");
    printf("  no bautizado que fue\n");
    printf("  abandonado. Su llanto\n");
    printf("  despierta compasion.\n");
    printf("   \n");
    printf("  Pero cuando un viajero\n");
    printf("  lo toma en brazos para\n");
    printf("  ayudarlo, el bebe muestra\n");
    printf("  dientes de demonio y\n");
    printf("  ataca sin piedad.\n");
    printf("   \n");
    printf("  Rol: SORPRESA\n");
    printf("  Robo de cartas constante\n");
    printf("  y ataques enganosos.\n");
    break;
case 11:
    printf("   ========================\n");
    printf("   %s\n", NOMBRES_PERSONAJES[11]);
    printf("   ========================\n\n");
    printf("  El fantasma de una mujer\n");
    printf("  que ronda un antiguo\n");
    printf("  arbol de tamarindo en una\n");
    printf("  hacienda costeña.\n");
    printf("   \n");
    printf("  Llora buscando consuelo,\n");
    printf("  pero si alguien se le\n");
    printf("  acerca, revela un rostro\n");
    printf("  horrendo que provoca\n");
    printf("  locura o la muerte.\n");
    printf("   \n");
    printf("  Rol: TRAMPA\n");
    printf("  Drenaje de vida, ilusiones\n");
    printf("  y control absoluto.\n");
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
                if (!cs->ya_robo_turno && !cs->carta_jugada_este_turno) {
                    printf("   X: Robar 1 carta (OBLIGATORIO)\n");
                } else {
                    printf("   A: Jugar esta carta\n");
                }
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

            int start_idx = gs->personaje_elegido - 1;
            if (start_idx < 0) start_idx = 0;
            if (start_idx > 12 - 3) start_idx = 12 - 3;
            for (int i = start_idx; i < start_idx + 3; i++) {
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
            } else if (cs->fase == COMBAT_ENEMY_WAIT) {
                printf("\n [RIVAL JUGANDO] Espera...\n");
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

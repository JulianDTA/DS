#include "combat.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// =====================================================
// ECUATRIALS - Gestor de Combate Completo
// =====================================================

static unsigned int ai_rng = 77777;
static int ai_rand() {
    ai_rng = ai_rng * 1103515245 + 12345;
    return (ai_rng >> 16) & 0x7FFF;
}

void combat_log(CombatState* cs, const char* msg) {
    if (cs->log_count >= 6) {
        for (int i = 0; i < 5; i++) {
            strncpy(cs->log[i], cs->log[i + 1], 31);
        }
        cs->log_count = 5;
    }
    strncpy(cs->log[cs->log_count], msg, 31);
    cs->log[cs->log_count][31] = '\0';
    cs->log_count++;
}

void combat_init(CombatState* cs,
                 const char* nombre_jugador, const CardData* deck_jugador, int deck_size_j,
                 const char* nombre_rival, const CardData* deck_rival, int deck_size_r)
{
    memset(cs, 0, sizeof(CombatState));

    cs->jugador.nombre = nombre_jugador;
    cs->jugador.hp = 10;
    cs->jugador.max_hp = 10;
    cs->jugador.puede_jugar_otra = false;
    deck_init(&cs->jugador.deck, deck_jugador, deck_size_j);

    cs->rival.nombre = nombre_rival;
    cs->rival.hp = 10;
    cs->rival.max_hp = 10;
    cs->rival.puede_jugar_otra = false;
    deck_init(&cs->rival.deck, deck_rival, deck_size_r);

    cs->fase = COMBAT_START;
    cs->turno = 0;
    cs->cursor = 0;
    cs->carta_jugada_este_turno = false;
    cs->log_count = 0;
    cs->ya_robo_turno = false;

    // Mano inicial: 3 cartas cada uno
    deck_draw(&cs->jugador.deck, 3);
    deck_draw(&cs->rival.deck, 3);

    ai_rng = (unsigned int)(REG_VCOUNT * 3571 + 13);

    combat_log(cs, "Comienza la batalla!");
}

void combat_resolve_card(CombatState* cs, Fighter* atacante, Fighter* defensor, const CardData* carta) {
    char buf[32];

    // --- ESCUDO ---
    if (carta->efectos & FX_SHIELD) {
        deck_add_shield(&atacante->deck, carta->escudo);
        snprintf(buf, 31, "+%d Escudo!", carta->escudo);
        combat_log(cs, buf);
    }

    // --- CURACION ---
    if (carta->efectos & FX_HEAL) {
        atacante->hp += carta->curacion;
        if (atacante->hp > atacante->max_hp)
            atacante->hp = atacante->max_hp;
        snprintf(buf, 31, "+%d HP! (HP:%d)", carta->curacion, atacante->hp);
        combat_log(cs, buf);
    }

    // --- ROBAR CARTAS ---
    if (carta->efectos & FX_DRAW) {
        deck_draw(&atacante->deck, carta->robar);
        snprintf(buf, 31, "Roba %d carta(s)", carta->robar);
        combat_log(cs, buf);
    }

    // --- ATAQUE ---
    if (carta->efectos & FX_ATTACK) {
        int dano = carta->ataque;
        int dano_restante = deck_damage_shields(&defensor->deck, dano);

        if (dano_restante < dano) {
            int absorbido = dano - dano_restante;
            snprintf(buf, 31, "Escudo absorbe %d!", absorbido);
            combat_log(cs, buf);
        }

        if (dano_restante > 0) {
            defensor->hp -= dano_restante;
            if (defensor->hp < 0) defensor->hp = 0;
            snprintf(buf, 31, "-%d HP! (%s:%d)", dano_restante, defensor->nombre, defensor->hp);
            combat_log(cs, buf);
        }
    }

    // --- JUGAR OTRA VEZ ---
    if (carta->efectos & FX_PLAY_AGAIN) {
        atacante->puede_jugar_otra = true;
    }
}

void combat_ai_turn(CombatState* cs) {
    Fighter* ai = &cs->rival;

    // Robar 1 carta al inicio del turno
    deck_draw(&ai->deck, 1);

    // Regla de mano vacia
    if (ai->deck.mano_size == 0) {
        deck_draw(&ai->deck, 2);
    }

    char buf[32];
    snprintf(buf, 31, "-- Turno de %s --", ai->nombre);
    combat_log(cs, buf);

    // IA juega UNA carta (a menos que tenga PLAY_AGAIN)
    bool puede_jugar = true;
    while (puede_jugar && ai->deck.mano_size > 0) {
        puede_jugar = false;
        ai->puede_jugar_otra = false;

        // Estrategia: priorizar curacion si HP < 4, sino atacar
        int mejor_idx = 0;
        int mejor_puntaje = -1;

        for (int i = 0; i < ai->deck.mano_size; i++) {
            const CardData* c = ai->deck.mano[i];
            int puntaje = 0;

            if (ai->hp <= 4 && (c->efectos & FX_HEAL)) puntaje += 10;
            if (c->efectos & FX_ATTACK) puntaje += c->ataque;
            if (c->efectos & FX_SHIELD) puntaje += 3;
            if (c->efectos & FX_PLAY_AGAIN) puntaje += 4;
            if (c->efectos & FX_DRAW) puntaje += 2;
            puntaje += ai_rand() % 3;

            if (puntaje > mejor_puntaje) {
                mejor_puntaje = puntaje;
                mejor_idx = i;
            }
        }

        const CardData* carta = deck_play_from_hand(&ai->deck, mejor_idx);
        if (carta) {
            snprintf(buf, 31, "%s juega %s", ai->nombre, carta->nombre);
            combat_log(cs, buf);
            combat_resolve_card(cs, ai, &cs->jugador, carta);

            // Solo sigue jugando si la carta tenia PLAY_AGAIN
            if (ai->puede_jugar_otra && ai->deck.mano_size > 0) {
                puede_jugar = true;
                ai->puede_jugar_otra = false;
                combat_log(cs, "Encadena otra carta!");
            }
        }
    }
}

void combat_update(CombatState* cs, int keys_down) {
    switch (cs->fase) {
        case COMBAT_START:
            cs->fase = COMBAT_PLAYER_DRAW;
            break;

        case COMBAT_PLAYER_DRAW:
            cs->turno++;
            cs->carta_jugada_este_turno = false;
            cs->jugador.puede_jugar_otra = false;
            cs->ya_robo_turno = false;

            {
                char buf[32];
                snprintf(buf, 31, "-- Tu Turno %d --", cs->turno);
                combat_log(cs, buf);
            }

            cs->cursor = 0;
            cs->fase = COMBAT_PLAYER_TURN;
            break;

        case COMBAT_PLAYER_TURN:
            // --- X: ROBAR CARTA ---
            // Solo puedes robar una vez por turno, antes de jugar
            if ((keys_down & KEY_X) && !cs->ya_robo_turno && !cs->carta_jugada_este_turno) {
                deck_draw(&cs->jugador.deck, 1);
                cs->ya_robo_turno = true;
                combat_log(cs, "Robas 1 carta.");
                
                // Si la mano estaba vacia, robar 2
                if (cs->jugador.deck.mano_size == 0) {
                    deck_draw(&cs->jugador.deck, 2);
                    combat_log(cs, "Mano vacia! +2 cartas.");
                }
            }

            // --- NAVEGACION ---
            if (keys_down & KEY_LEFT) {
                cs->cursor--;
                if (cs->cursor < 0) cs->cursor = cs->jugador.deck.mano_size - 1;
            }
            if (keys_down & KEY_RIGHT) {
                cs->cursor++;
                if (cs->cursor >= cs->jugador.deck.mano_size) cs->cursor = 0;
            }

            // --- A: JUGAR CARTA ---
            // REGLA: Debes robar primero (X) antes de poder jugar
            if ((keys_down & KEY_A) && cs->jugador.deck.mano_size > 0 && cs->ya_robo_turno) {
                cs->jugador.puede_jugar_otra = false;

                const CardData* carta = deck_play_from_hand(&cs->jugador.deck, cs->cursor);
                if (carta) {
                    char buf[32];
                    snprintf(buf, 31, "Juegas %s!", carta->nombre);
                    combat_log(cs, buf);

                    combat_resolve_card(cs, &cs->jugador, &cs->rival, carta);
                    cs->carta_jugada_este_turno = true;

                    // Ajustar cursor
                    if (cs->cursor >= cs->jugador.deck.mano_size && cs->jugador.deck.mano_size > 0) {
                        cs->cursor = cs->jugador.deck.mano_size - 1;
                    }
                    if (cs->cursor < 0) cs->cursor = 0;

                    // Verificar K.O.
                    if (cs->rival.hp <= 0) {
                        cs->fase = COMBAT_CHECK_WIN;
                        break;
                    }

                    // Si la carta tenia PLAY_AGAIN y hay cartas en la mano, sigue tu turno
                    if (cs->jugador.puede_jugar_otra && cs->jugador.deck.mano_size > 0) {
                        cs->jugador.puede_jugar_otra = false;
                        combat_log(cs, "Encadena otra carta!");
                        // Sigue en COMBAT_PLAYER_TURN, puede jugar otra
                        break;
                    }

                    // Si NO tenia PLAY_AGAIN, el turno termina automaticamente
                    combat_log(cs, "Fin de tu turno.");
                    cs->fase = COMBAT_ENEMY_TURN;
                }
            }
            break;

        case COMBAT_ENEMY_TURN:
            combat_ai_turn(cs);

            if (cs->jugador.hp <= 0) {
                cs->fase = COMBAT_CHECK_WIN;
            } else {
                cs->fase = COMBAT_PLAYER_DRAW;
            }
            break;

        case COMBAT_CHECK_WIN:
            if (cs->rival.hp <= 0) {
                combat_log(cs, "VICTORIA!");
                cs->fase = COMBAT_WIN;
            } else if (cs->jugador.hp <= 0) {
                combat_log(cs, "DERROTA...");
                cs->fase = COMBAT_LOSE;
            }
            break;

        case COMBAT_WIN:
        case COMBAT_LOSE:
            break;

        default:
            break;
    }
}

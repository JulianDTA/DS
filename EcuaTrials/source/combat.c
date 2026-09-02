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
    cs->jugador.num_reglas = 0;
    deck_init(&cs->jugador.deck, deck_jugador, deck_size_j);

    cs->rival.nombre = nombre_rival;
    cs->rival.hp = 10;
    cs->rival.max_hp = 10;
    cs->rival.puede_jugar_otra = false;
    cs->rival.num_reglas = 0;
    deck_init(&cs->rival.deck, deck_rival, deck_size_r);

    cs->fase = COMBAT_START;
    cs->turno = 0;
    cs->cursor = 0;
    cs->carta_jugada_este_turno = false;
    cs->ya_robo_turno = false;
    cs->log_count = 0;
    cs->timer = 0;
    cs->dragged_card_idx = -1;
    cs->drag_x = 0;
    cs->drag_y = 0;
    cs->last_tapped_idx = -1;
    cs->double_tap_timer = 0;
    cs->force_play = false;

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
        snprintf(buf, 31, "%s: +%d Escudo", atacante->nombre, carta->escudo);
        combat_log(cs, buf);
    }

    // --- CURACION ---
    if (carta->efectos & FX_HEAL) {
        atacante->hp += carta->curacion;
        if (atacante->hp > atacante->max_hp)
            atacante->hp = atacante->max_hp;
        snprintf(buf, 31, "%s: +%d HP", atacante->nombre, carta->curacion);
        combat_log(cs, buf);
    }

    // --- ROBAR CARTAS ---
    if (carta->efectos & FX_DRAW) {
        if (deck_draw(&atacante->deck, carta->robar)) combat_log(cs, "Mazo reiniciado!");
        snprintf(buf, 31, "%s: Roba %d", atacante->nombre, carta->robar);
        combat_log(cs, buf);
    }

    // --- ROBAR CARTA DEL RIVAL (HAND) ---
    if (carta->efectos & FX_STEAL_HAND) {
        if (defensor->deck.mano_size > 0) {
            int r = deck_rng_next() % defensor->deck.mano_size;
            const CardData* stolen = defensor->deck.mano[r];
            for (int j = r; j < defensor->deck.mano_size - 1; j++) {
                defensor->deck.mano[j] = defensor->deck.mano[j+1];
            }
            defensor->deck.mano_size--;
            if (atacante->deck.mano_size < MAX_HAND_SIZE) {
                atacante->deck.mano[atacante->deck.mano_size++] = stolen;
            } else if (atacante->deck.descarte_size < MAX_DECK_SIZE) {
                atacante->deck.descarte[atacante->deck.descarte_size++] = stolen;
            }
            snprintf(buf, 31, "%s roba carta rival", atacante->nombre);
            combat_log(cs, buf);
        } else {
            combat_log(cs, "Mano rival vacia!");
        }
    }
    
    if (carta->efectos & FX_STEAL_DECK) {
        bool sf = false;
        const CardData* robada = deck_steal_top_from_deck(&defensor->deck, &sf);
        if (sf) combat_log(cs, "Mazo rival reiniciado!");
        if (robada) {
            deck_add_to_hand(&atacante->deck, robada);
            combat_log(cs, "Roba 1 carta del mazo rival!");
        }
    }
    
    if (carta->efectos & FX_STEAL_DISCARD) {
        const CardData* robada = deck_steal_random_from_discard(&defensor->deck);
        if (robada) {
            deck_add_to_hand(&atacante->deck, robada);
            combat_log(cs, "Roba 1 carta del descarte!");
        } else {
            combat_log(cs, "Descarte rival vacio!");
        }
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
            snprintf(buf, 31, "%s recibe %d dmg", defensor->nombre, dano_restante);
            combat_log(cs, buf);
        }
    }

    // --- JUGAR OTRA VEZ ---
    if (carta->efectos & FX_PLAY_AGAIN) {
        atacante->puede_jugar_otra = true;
    }
    
    // --- AURA (ESTADO / REGLA) ---
    if (carta->efectos & FX_AURA) {
        // Remover del descarte porque se queda activa
        if (atacante->deck.descarte_size > 0 && atacante->deck.descarte[atacante->deck.descarte_size - 1] == carta) {
            atacante->deck.descarte_size--;
        }
        
        // Anadir a las reglas activas (max 3)
        if (atacante->num_reglas >= 3) {
            // Enviar la mas antigua al descarte
            if (atacante->deck.descarte_size < MAX_DECK_SIZE) {
                atacante->deck.descarte[atacante->deck.descarte_size++] = atacante->reglas_activas[0];
            }
            
            // Desplazar (Shift)
            atacante->reglas_activas[0] = atacante->reglas_activas[1];
            atacante->reglas_activas[1] = atacante->reglas_activas[2];
            atacante->num_reglas = 2;
        }
        
        atacante->reglas_activas[atacante->num_reglas++] = carta;
        combat_log(cs, "Regla en campo!");
    }
}


void combat_apply_auras(CombatState* cs, Fighter* owner, Fighter* opponent) {
    for (int i = 0; i < owner->num_reglas; i++) {
        const CardData* aura = owner->reglas_activas[i];
        
        // Efectos pasivos
        if (aura->ataque > 0) {
            char buf[32];
            int dmg = deck_damage_shields(&opponent->deck, aura->ataque);
            if (dmg > 0) {
                opponent->hp -= dmg;
                snprintf(buf, 31, "Aura: -%d HP a %s", dmg, opponent->nombre);
            } else {
                snprintf(buf, 31, "Aura choca con escudo");
            }
            combat_log(cs, buf);
        }
        
        if (aura->curacion > 0) {
            char buf[32];
            owner->hp += aura->curacion;
            if (owner->hp > owner->max_hp) owner->hp = owner->max_hp;
            snprintf(buf, 31, "Aura cura: +%d HP", aura->curacion);
            combat_log(cs, buf);
        }
        
        if (aura->robar > 0) {
            if (deck_draw(&owner->deck, aura->robar)) combat_log(cs, "Mazo reiniciado!");
            combat_log(cs, "Aura: Roba extra");
        }
    }
}

void combat_ai_turn(CombatState* cs) {
    Fighter* ai = &cs->rival;

    char buf[32];
    snprintf(buf, 31, "-- Turno de %s --", ai->nombre);
    combat_log(cs, buf);

    // IA juega UNA carta (si la anterior no tuvo PLAY_AGAIN, termina su turno en la maquina de estados)
    ai->puede_jugar_otra = false;

    if (ai->deck.mano_size > 0) {
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
            snprintf(buf, 31, "Juega: %s", carta->nombre);
            combat_log(cs, buf);
            combat_resolve_card(cs, ai, &cs->jugador, carta);
            
            if (ai->deck.mano_size == 0) {
                if (deck_draw(&ai->deck, 2)) combat_log(cs, "Rival mazo reiniciado!");
                combat_log(cs, "Rival mano vacia! +2");
            }

            if (ai->puede_jugar_otra) {
                combat_log(cs, "Encadena otra carta!");
            }
        }
    } else {
        combat_log(cs, "Sin cartas que jugar.");
    }
}

void combat_update(CombatState* cs, int keys_down, touchPosition* touch) {
    if (cs->double_tap_timer > 0) cs->double_tap_timer--;
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
            combat_apply_auras(cs, &cs->jugador, &cs->rival);
            if (cs->rival.hp <= 0) cs->fase = COMBAT_CHECK_WIN;
            else cs->fase = COMBAT_PLAYER_TURN;
            break;

        case COMBAT_PLAYER_TURN: {
            int tch_down = keys_down; // keys_down viene de keysDown()
            int tch_held = keysHeld();
            int tch_up   = keysUp();
            
            if (tch_down & KEY_TOUCH) {
                bool touched_card = false;
                // Chequear cartas en mano primero para evitar superposicion
                for (int i = 0; i < cs->jugador.deck.mano_size; i++) {
                    int cx = get_card_x(i, cs->jugador.deck.mano_size);
                    int cy = 120;
                    if (touch->px >= cx && touch->px <= cx + 32 &&
                        touch->py >= cy && touch->py <= cy + 64) {
                        cs->dragged_card_idx = i;
                        cs->drag_x = touch->px - 16;
                        cs->drag_y = touch->py - 32;
                        
                        // Check double tap
                        if (cs->last_tapped_idx == i && cs->double_tap_timer > 0) {
                            cs->force_play = true;
                        }
                        cs->last_tapped_idx = i;
                        cs->double_tap_timer = 20; // ~1/3 of a second to double tap
                        
                        touched_card = true;
                        break;
                    }
                }
                
                // Si no toco una carta, chequear Mazo (zona inferior derecha)
                if (!touched_card && touch->px > 200 && touch->py > 110) {
                    if (!cs->ya_robo_turno && !cs->carta_jugada_este_turno) {
                        if (cs->jugador.deck.mano_size == 0) {
                            if (deck_draw(&cs->jugador.deck, 2)) combat_log(cs, "Mazo reiniciado!");
                            combat_log(cs, "Mano vacia! Recarga +2");
                        } else {
                            if (deck_draw(&cs->jugador.deck, 1)) combat_log(cs, "Mazo reiniciado!");
                            combat_log(cs, "Robas 1 carta.");
                        }
                        cs->ya_robo_turno = true;
                    }
                }
            } else if (tch_held & KEY_TOUCH) {
                if (cs->dragged_card_idx >= 0) {
                    int target_x = touch->px - 16;
                    int target_y = touch->py - 32;
                    
                    // Deadzone to prevent touchscreen hardware jitter
                    if (abs(target_x - cs->drag_x) > 1) cs->drag_x = target_x;
                    if (abs(target_y - cs->drag_y) > 1) cs->drag_y = target_y;
                }
            } else if (tch_up & KEY_TOUCH) {
                if (cs->dragged_card_idx >= 0) {
                    if (cs->drag_y < 60 || cs->force_play) { // Drop zone (borde superior)
                        if (cs->ya_robo_turno) {
                            cs->jugador.puede_jugar_otra = false;
                            const CardData* carta = deck_play_from_hand(&cs->jugador.deck, cs->dragged_card_idx);
                            
                            if (carta) {
                                char buf[32];
                                snprintf(buf, 31, "Juegas %s!", carta->nombre);
                                combat_log(cs, buf);

                                combat_resolve_card(cs, &cs->jugador, &cs->rival, carta);
                                cs->carta_jugada_este_turno = true;

                                if (cs->jugador.deck.mano_size == 0) {
                                    if (deck_draw(&cs->jugador.deck, 2)) combat_log(cs, "Mazo reiniciado!");
                                    combat_log(cs, "Mano vacia! Recarga +2");
                                }

                                if (cs->rival.hp <= 0) {
                                    cs->fase = COMBAT_CHECK_WIN;
                                } else if (cs->jugador.puede_jugar_otra && cs->jugador.deck.mano_size > 0) {
                                    cs->jugador.puede_jugar_otra = false;
                                    combat_log(cs, "Encadena otra carta!");
                                } else {
                                    combat_log(cs, "Fin de tu turno.");
                                    cs->ya_robo_turno = false;
                                    cs->fase = COMBAT_ENEMY_THINKING;
                                    cs->timer = 60;
                                }
                            }
                        } else {
                            combat_log(cs, "Debes robar mazo primero!");
                        }
                    }
cs->dragged_card_idx = -1;
                    cs->force_play = false;
                }
            }
            break;
        }

        case COMBAT_ENEMY_THINKING:
            if (cs->timer > 0) {
                cs->timer--;
            } else {
                cs->fase = COMBAT_ENEMY_TURN;
            }
            break;

        case COMBAT_ENEMY_TURN:
            if (!cs->ya_robo_turno) {
                combat_apply_auras(cs, &cs->rival, &cs->jugador);
                if (cs->jugador.hp <= 0) { cs->fase = COMBAT_CHECK_WIN; break; }
                if (cs->rival.deck.mano_size == 0) {
                    if (deck_draw(&cs->rival.deck, 2)) combat_log(cs, "Rival mazo reiniciado!");
                    combat_log(cs, "Rival mano vacia! +2");
                } else {
                    if (deck_draw(&cs->rival.deck, 1)) combat_log(cs, "Rival mazo reiniciado!");
                }
                cs->ya_robo_turno = true;
            }
            // IA: Juega 1 sola carta y pasa a un estado de espera con timer
            combat_ai_turn(cs);
            cs->timer = 150; // 2.5 segundos a 60 FPS
            cs->fase = COMBAT_ENEMY_WAIT;
            break;

        case COMBAT_ENEMY_WAIT:
            cs->timer--;
            if (cs->timer <= 0) {
                // Si la IA puede jugar otra carta por un combo, vuelve a su turno
                if (cs->rival.puede_jugar_otra && cs->rival.deck.mano_size > 0) {
                    cs->rival.puede_jugar_otra = false;
                    cs->fase = COMBAT_ENEMY_THINKING;
                    cs->timer = 60;
                } else {
                    // Si no, verificar K.O. o devolver turno al jugador
                    char buf[32];
                    snprintf(buf, 31, "Fin del turno de %s", cs->rival.nombre);
                    combat_log(cs, buf);
                    if (cs->jugador.hp <= 0) {
                        cs->fase = COMBAT_CHECK_WIN;
                    } else {
                        cs->fase = COMBAT_PLAYER_DRAW;
                    }
                }
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

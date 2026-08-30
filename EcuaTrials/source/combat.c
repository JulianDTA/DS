#include "combat.h"
#include <stdio.h>

// [0] = Jugador Local, [1] = Rival / IA
static PlayerState players[2];

void init_combat(void) {
    for (int i = 0; i < 2; i++) {
        players[i].max_hp = 10;
        players[i].hp = 10;
        players[i].shield = 0;
        // Comenzamos con baja energía que irá subiendo cada turno
        players[i].max_energy = 1;
        players[i].energy = 1;
    }
}

PlayerState* get_player_state(int player_id) {
    if (player_id < 0 || player_id > 1) return &players[0];
    return &players[player_id];
}

void take_damage(int target_id, int amount) {
    PlayerState* target = &players[target_id];
    
    if (amount <= 0) return;

    printf("  -> Recibiendo %d de dano!\n", amount);

    // Regla estricta: Romper escudo primero
    if (target->shield > 0) {
        if (amount >= target->shield) {
            printf("  -> Escudo roto! (%d absorbido)\n", target->shield);
            amount -= target->shield;
            target->shield = 0;
        } else {
            target->shield -= amount;
            printf("  -> Escudo resiste! (Restante: %d)\n", target->shield);
            amount = 0;
        }
    }

    // El daño sobrante va directamente a la vida (HP)
    if (amount > 0) {
        target->hp -= amount;
        if (target->hp < 0) target->hp = 0;
        printf("  -> Impacto a vida! (HP restante: %d)\n", target->hp);
        
        if (target->hp == 0) {
            printf("\n  [!] K.O.! LEYENDA DERROTADA!\n");
        }
    }
}

bool play_card(int player_id, const CardData* card) {
    PlayerState* p = &players[player_id];
    int enemy_id = (player_id == 0) ? 1 : 0;
    
    // Validar economía de energía
    if (p->energy < card->costo) {
        printf("  [X] Energia insuficiente (%d/%d) para %s\n", p->energy, card->costo, card->nombre);
        return false;
    }
    
    // Pagar costo de la carta
    p->energy -= card->costo;
    printf("\n  [+] Has jugado: %s\n", card->nombre);
    
    // Aplicar efectos defensivos y de curación (Buffs a sí mismo)
    if (card->defense > 0) {
        p->shield += card->defense;
        printf("  -> Ganas %d de escudo. (Total: %d)\n", card->defense, p->shield);
    }
    
    if (card->heal > 0) {
        p->hp += card->heal;
        if (p->hp > p->max_hp) p->hp = p->max_hp; // No curar por encima del máximo
        printf("  -> Te curas %d HP. (Total: %d)\n", card->heal, p->hp);
    }
    
    // Aplicar efectos ofensivos (Daño al rival)
    if (card->damage > 0) {
        take_damage(enemy_id, card->damage);
    }
    
    return true;
}

import sys

with open('source/combat.c', 'r') as f:
    code = f.read()

aura_func = """
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
"""

code = code.replace("void combat_ai_turn(CombatState* cs) {", aura_func + "\nvoid combat_ai_turn(CombatState* cs) {")

old_player = """            cs->cursor = 0;
            cs->fase = COMBAT_PLAYER_TURN;
            break;"""
            
new_player = """            cs->cursor = 0;
            combat_apply_auras(cs, &cs->jugador, &cs->rival);
            if (cs->rival.hp <= 0) cs->fase = COMBAT_CHECK_WIN;
            else cs->fase = COMBAT_PLAYER_TURN;
            break;"""

code = code.replace(old_player, new_player)

old_ai = """        case COMBAT_ENEMY_TURN:
            if (!cs->ya_robo_turno) {"""
new_ai = """        case COMBAT_ENEMY_TURN:
            if (!cs->ya_robo_turno) {
                combat_apply_auras(cs, &cs->rival, &cs->jugador);
                if (cs->jugador.hp <= 0) { cs->fase = COMBAT_CHECK_WIN; break; }"""

code = code.replace(old_ai, new_ai)

with open('source/combat.c', 'w') as f:
    f.write(code)

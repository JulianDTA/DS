import re

with open('generate_game_arrays.txt') as f:
    lines = f.readlines()
cases = "".join(lines[37:133])
arrays_code = "".join(lines[0:37])

with open('source/game.c') as f:
    code = f.read()

old_arrays = """static const char* NOMBRES_PERSONAJES[] = {"Cantuna", "Tin Tin", "La Tunda"};

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
}"""

code = code.replace(old_arrays, arrays_code.strip())

code = code.replace('if (gs->personaje_elegido < 0) gs->personaje_elegido = 2;', 'if (gs->personaje_elegido < 0) gs->personaje_elegido = 11;')
code = code.replace('if (gs->personaje_elegido > 2) gs->personaje_elegido = 0;', 'if (gs->personaje_elegido > 11) gs->personaje_elegido = 0;')
code = code.replace('gs->rival_elegido = (gs->personaje_elegido + 1) % 3;', 'gs->rival_elegido = (gs->personaje_elegido + 1) % 12;')

pattern = r'(case GAME_SELECT_CHAR:\n            printf\("\\n\\n"\);\n            switch \(gs->personaje_elegido\) \{\n)(.*?)(            \}\n            break;\n\n        case GAME_COMBAT:)'
code = re.sub(pattern, r'\g<1>' + cases.replace('\\', '\\\\') + r'\g<3>', code, flags=re.DOTALL)

old_loop = 'for (int i = 0; i < 3; i++) {'
new_loop = '''int start_idx = gs->personaje_elegido - 1;
            if (start_idx < 0) start_idx = 0;
            if (start_idx > 12 - 3) start_idx = 12 - 3;
            for (int i = start_idx; i < start_idx + 3; i++) {'''
code = code.replace(old_loop, new_loop)

old_a_btn = '''                printf("   A: Jugar esta carta\\n");
                if (!cs->ya_robo_turno && !cs->carta_jugada_este_turno)
                    printf("   X: Robar 1 carta\\n");'''
new_a_btn = '''                if (!cs->ya_robo_turno && !cs->carta_jugada_este_turno) {
                    printf("   X: Robar 1 carta (OBLIGATORIO)\\n");
                } else {
                    printf("   A: Jugar esta carta\\n");
                }'''
code = code.replace(old_a_btn, new_a_btn)

with open('source/game.c', 'w') as f:
    f.write(code)

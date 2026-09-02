import re

with open('source/game.c', 'r') as f:
    code = f.read()

# 1. card_x
code = code.replace('int x = i * 36 + 10;', 'int x = get_card_x(i, cs->jugador.deck.mano_size);')

# 2. sprites and palettes (lines 189-200 roughly)
sprite_code = '''        u16* p_gfx = (gs->personaje_elegido == 2) ? gfx_tunda : gfx_cantuna;
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
        }'''
old_sprite_code = '''        if (gfx_tunda) {
            // Jugador a la izquierda (Tunda)
            oamSet(&oamMain, 0, 10, 100, 0, 0, SpriteSize_64x64, SpriteColorFormat_256Color, 
                   gfx_tunda, -1, false, false, false, false, false);
        }
        if (gfx_cantuna) {
            // Rival a la derecha (Cantuna)
            oamSet(&oamMain, 1, 182, 100, 0, 0, SpriteSize_64x64, SpriteColorFormat_256Color, 
                   gfx_cantuna, -1, false, false, false, false, false);
        }'''
code = code.replace(old_sprite_code, sprite_code)

# 3. game_init bypass
code = code.replace('// Saltar el menu y la seleccion directamente a combate para debugear graficos\n    gs->fase = GAME_COMBAT;\n    \n    // Iniciar con personaje 0 vs personaje 1\n    gs->personaje_elegido = 0;\n    gs->rival_elegido = 1;\n    combat_init(&gs->combate, \n        NOMBRES_PERSONAJES[0], get_deck_for_char(0), get_deck_size_for_char(0),\n        NOMBRES_PERSONAJES[1], get_deck_for_char(1), get_deck_size_for_char(1));', 'gs->fase = GAME_TITLE;\n    gs->personaje_elegido = 0;\n    gs->rival_elegido = 1;')

# 4. game_draw_top screens
top_code = '''void game_draw_top(GameState* gs) {
    oamClear(&oamMain, 0, 128);
    consoleSelect(topConsole);
    printf("\\x1b[2J");
    
    if (gs->fase == GAME_TITLE) {
        printf("\\x1b[10;8HECUATRIALS\\n");
        printf("\\x1b[12;5HPulsa START para jugar\\n");
    } else if (gs->fase == GAME_SELECT_CHAR) {
        printf("\\x1b[10;5HSELECCION DE PERSONAJE\\n");
        printf("\\x1b[12;8H%s\\n", NOMBRES_PERSONAJES[gs->personaje_elegido]);
        printf("\\x1b[14;5HPulsa A para confirmar\\n");
        printf("\\x1b[16;5HPulsa B para volver\\n");
    } else if (gs->fase == GAME_RESULT) {
        printf("\\x1b[10;8HFIN DEL COMBATE\\n");
        printf("\\x1b[12;5HPulsa START para salir\\n");
    } else if (gs->fase == GAME_COMBAT) {
'''
code = code.replace('void game_draw_top(GameState* gs) {\n    oamClear(&oamMain, 0, 128);\n    \n    if (gs->fase == GAME_COMBAT) {\n        consoleSelect(topConsole);\n        printf("\\x1b[2J");\n', top_code)

# 5. game_draw_bottom screens
import sys
sys.path.append('source')
from restore_lore import cases_code

bottom_code = f'''    }} else if (gs->fase == GAME_TITLE) {{
        consoleSelect(subConsole);
        printf("\\\\x1b[2J");
        printf("\\\\n\\\\n\\\\n\\\\n\\\\n   BATALLAS MITOLOGICAS\\\\n   DEL ECUADOR\\\\n\\\\n   Presiona START en la\\\\n   pantalla superior.");
    }} else if (gs->fase == GAME_SELECT_CHAR) {{
        consoleSelect(subConsole);
        printf("\\\\x1b[2J");
        printf("\\\\n\\\\n");
        switch (gs->personaje_elegido) {{
{cases_code.replace('\\n', '\\\\n')}
        }}
    }} else if (gs->fase == GAME_RESULT) {{
        consoleSelect(subConsole);
        printf("\\\\x1b[2J");
        int winner = (gs->combate.jugador.hp > 0) ? gs->personaje_elegido : gs->rival_elegido;
        int loser = (gs->combate.jugador.hp > 0) ? gs->rival_elegido : gs->personaje_elegido;
        bool pwon = (gs->combate.jugador.hp > 0);
        print_match_result(winner, loser, pwon);
    }}
}}
'''
code = re.sub(r'    \}\n\}\n$', bottom_code, code)

with open('source/game.c', 'w') as f:
    f.write(code)

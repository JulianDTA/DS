import re

with open('source/game.c', 'r') as f:
    code = f.read()

replacement = '''void game_draw_top(GameState* gs) {
    oamClear(&oamMain, 0, 128);
    consoleSelect(topConsole);
    printf("\\\\x1b[2J");
    
    if (gs->fase == GAME_TITLE) {
        printf("\\\\x1b[4;8HECUATRIALS\\\\n");
        printf("\\\\x1b[6;5HPulsa START para jugar\\\\n");
    } else if (gs->fase == GAME_SELECT_CHAR) {
        printf("\\\\x1b[2;5HSELECCION DE PERSONAJE\\\\n");
        printf("\\\\x1b[4;8H%s\\\\n", NOMBRES_PERSONAJES[gs->personaje_elegido]);
        printf("\\\\x1b[6;5HPulsa A para confirmar\\\\n");
        printf("\\\\x1b[7;5HPulsa B para volver\\\\n");
    } else if (gs->fase == GAME_RESULT) {
        printf("\\\\x1b[4;8HFIN DEL COMBATE\\\\n");
        printf("\\\\x1b[6;5HPulsa START para salir\\\\n");
    } else if (gs->fase == GAME_COMBAT) {
        // Player (Left) - moved to bottom of top screen
        printf("\\\\x1b[21;1H%s", gs->combate.jugador.nombre);
        printf("\\\\x1b[22;1HHP: %d/%d", gs->combate.jugador.hp, gs->combate.jugador.max_hp);
        printf("\\\\x1b[23;1HDEF: %d", deck_get_total_shield(&gs->combate.jugador.deck));
        
        // Rival (Right) - moved to bottom of top screen
        printf("\\\\x1b[21;18H%s", gs->combate.rival.nombre);
        printf("\\\\x1b[22;18HHP: %d/%d", gs->combate.rival.hp, gs->combate.rival.max_hp);
        printf("\\\\x1b[23;18HDEF: %d", deck_get_total_shield(&gs->combate.rival.deck));
        
        // Combat Log (Center Top, Rows 2-7) stays in the sky!
        for (int i = 0; i < gs->combate.log_count; i++) {
            char* msg = gs->combate.log[i];
            int len = 0; while (msg[len]) len++;
            int col = (32 - len) / 2;
            if (col < 1) col = 1;
            printf("\\\\x1b[%d;%dH%s", i + 2, col, msg);
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
}'''

code = re.sub(r'void game_draw_top\(GameState\* gs\).*?\}\n\}\n', replacement + '\n', code, flags=re.DOTALL)

with open('source/game.c', 'w') as f:
    f.write(code)

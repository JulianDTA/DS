import re
with open('source/game.c', 'r') as f:
    code = f.read()

# Add else if blocks at the end of game_draw_bottom
from source.restore_lore import cases_code

bottom_addon = f'''
    }} else if (gs->fase == GAME_TITLE) {{
        consoleSelect(subConsole);
        printf("\\\\x1b[2J");
        printf("\\\\n\\\\n\\\\n\\\\n\\\\n   BATALLAS MITOLOGICAS\\\\n   DEL ECUADOR\\\\n\\\\n   Presiona START en la\\\\n   pantalla superior.");
    }} else if (gs->fase == GAME_SELECT_CHAR) {{
        consoleSelect(subConsole);
        printf("\\\\x1b[2J");
        printf("\\\\n\\\\n");
        switch (gs->personaje_elegido) {{
{cases_code.replace('\\\\', '\\\\\\\\')}
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

# Replace the very last closing brace of game_draw_bottom
code = re.sub(r'    \}\n\}\n$', bottom_addon, code)

with open('source/game.c', 'w') as f:
    f.write(code)

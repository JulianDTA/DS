import re

from source.restore_lore import lores

cases_code = ""
for i in range(12):
    cases_code += f"        case {i}:\n"
    cases_code += f"            printf(\"\\\\x1b[3;4H%s\\\\n\\\\n\", NOMBRES_PERSONAJES[{i}]);\n"
    row = 5
    for line in lores[i]:
        cases_code += f"            printf(\"\\\\x1b[{row};3H{line}\");\n"
        row += 1
    cases_code += "            break;\n"

with open('source/game.c', 'r') as f:
    code = f.read()

# I will replace from } else if (gs->fase == GAME_TITLE) { to the end of the file.
bottom_part = f'''    }} else if (gs->fase == GAME_TITLE) {{
        consoleSelect(subConsole);
        printf("\\\\x1b[2J");
        printf("\\\\x1b[5;4HBATALLAS MITOLOGICAS");
        printf("\\\\x1b[6;4HDEL ECUADOR");
        printf("\\\\x1b[9;4HPresiona START en la");
        printf("\\\\x1b[10;4Hpantalla superior.");
    }} else if (gs->fase == GAME_SELECT_CHAR) {{
        consoleSelect(subConsole);
        printf("\\\\x1b[2J");
        switch (gs->personaje_elegido) {{
{cases_code}        }}
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

# Find } else if (gs->fase == GAME_TITLE) {
idx = code.find('    } else if (gs->fase == GAME_TITLE) {')
if idx != -1:
    code = code[:idx] + bottom_part

with open('source/game.c', 'w') as f:
    f.write(code)

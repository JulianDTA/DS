import re

with open('source/game.c', 'r') as f:
    code = f.read()

replacement = '''static void print_match_result(int winner, int loser, bool player_won) {
    if (player_won) {
        printf("\\\\x1b[3;4HFELICIDADES!");
        printf("\\\\x1b[5;4H%s ha vencido", NOMBRES_PERSONAJES[winner]);
        printf("\\\\x1b[6;4Ha %s!", NOMBRES_PERSONAJES[loser]);
    } else {
        printf("\\\\x1b[3;4HHAS CAIDO...");
        printf("\\\\x1b[5;4H%s fue derrotado", NOMBRES_PERSONAJES[loser]);
        printf("\\\\x1b[6;4Hpor %s.", NOMBRES_PERSONAJES[winner]);
    }
    printf("\\\\x1b[9;4H\\\"");
    
    // Line 9 and 10 for the quote
    if (winner == 0 && loser == 7) printf("\\\\x1b[9;5HEl oro del diablo supera\\\\x1b[10;5Ha la magia oscura.");
    else if (winner == 8 && loser == 9) printf("\\\\x1b[9;5HEl paramo no tiene\\\\x1b[10;5Hpiedad de las lagrimas.");
    else if (winner == 9 && loser == 10) printf("\\\\x1b[9;5HUn bebe mas arrastrado\\\\x1b[10;5Hal fondo del rio...");
    else if (winner == 4 && loser == 1) printf("\\\\x1b[9;5HEl seductor cayo\\\\x1b[10;5Hen la trampa mortal.");
    else if (winner == 3 && loser == 7) printf("\\\\x1b[9;5HAlmeida seguira bebiendo;\\\\x1b[10;5Hel otro seguira penando.");
    else if (winner == 6 && loser == 0) printf("\\\\x1b[9;5HLa Catedral impone\\\\x1b[10;5Hsu ley sobre San Francisco.");
    else if (winner == 5 && loser == 9) printf("\\\\x1b[9;5HTus llantos no callaran\\\\x1b[10;5Hmis gritos de culpa!");
    else if (winner == 10 && loser == 11) printf("\\\\x1b[9;5HUn demonio pequenito\\\\x1b[10;5Hgano a la tentacion.");
    else if (winner == 2 && loser == 5) printf("\\\\x1b[9;5HLa nina traviesa termino\\\\x1b[10;5Hentundada en el manglar.");
    else if (winner == 1 && loser == 8) printf("\\\\x1b[9;5HEl duende robo el orgullo\\\\x1b[10;5Hdel monstruo andino.");
    else if (winner == 7 && loser == 4) printf("\\\\x1b[9;5HNi tu perfume apagara\\\\x1b[10;5Hlas llamas del infierno.");
    else if (winner == 11 && loser == 3) printf("\\\\x1b[9;5HVen, padrecito, acercate\\\\x1b[10;5Hal tamarindo...");
    else printf("\\\\x1b[9;5HEl destino favorece\\\\x1b[10;5Hal vencedor hoy.");
    printf("\\\"");
}'''

code = re.sub(r'static void print_match_result\(int winner, int loser, bool player_won\) \{.*?(?=void game_draw_top)', replacement + '\n\n', code, flags=re.DOTALL)

with open('source/game.c', 'w') as f:
    f.write(code)

static void print_match_result(int winner, int loser, bool player_won) {
    printf("\n\n\n");
    if (player_won) {
        printf("   FELICIDADES!\n\n");
        printf("   %s ha vencido\n", NOMBRES_PERSONAJES[winner]);
        printf("   a %s!\n\n", NOMBRES_PERSONAJES[loser]);
    } else {
        printf("   HAS CAIDO...\n\n");
        printf("   %s fue derrotado\n", NOMBRES_PERSONAJES[loser]);
        printf("   por %s.\n\n", NOMBRES_PERSONAJES[winner]);
    }
    printf("   \"");
    if (winner == 0 && loser == 7) printf("%s", "El oro del diablo supera\n   a la magia oscura.");
    else if (winner == 8 && loser == 9) printf("%s", "El paramo no tiene\n   piedad de las lagrimas.");
    else if (winner == 9 && loser == 10) printf("%s", "Un bebe mas arrastrado\n   al fondo del rio...");
    else if (winner == 4 && loser == 1) printf("%s", "El seductor cayo\n   en la trampa mortal.");
    else if (winner == 3 && loser == 7) printf("%s", "Almeida seguira bebiendo;\n   el otro seguira penando.");
    else if (winner == 6 && loser == 0) printf("%s", "La Catedral impone\n   su ley sobre San Francisco.");
    else if (winner == 5 && loser == 9) printf("%s", "Tus llantos no callaran\n   mis gritos de culpa!");
    else if (winner == 10 && loser == 11) printf("%s", "Un demonio pequenito\n   gano a la tentacion.");
    else if (winner == 2 && loser == 5) printf("%s", "La nina traviesa termino\n   entundada en el manglar.");
    else if (winner == 11 && loser == 3) printf("%s", "La farra termino bajo\n   el arbol de tamarindo.");
    else if (winner == 0) printf("%s", "La arquitectura perfecta\n   nunca se derrumba.");
    else if (winner == 1) printf("%s", "Una travesura rapida\n   fue mas que suficiente.");
    else if (winner == 2) printf("%s", "Nadie escapa vivo de\n   los manglares...");
    else if (winner == 3) printf("%s", "Hasta la vuelta, senor!\n   Y a seguir bebiendo.");
    else if (winner == 4) printf("%s", "El terror absoluto\n   paralizo al oponente.");
    else if (winner == 5) printf("%s", "Devuelveme mis tripas!\n   La venganza esta servida.");
    else if (winner == 6) printf("%s", "Un canto de victoria\n   resuena en la plaza.");
    else if (winner == 7) printf("%s", "La magia de ultratumba\n   consumio su alma.");
    else if (winner == 8) printf("%s", "Fuerza bruta y salvaje\n   sin contemplaciones.");
    else if (winner == 9) printf("%s", "Tanto dolor y pena\n   terminan ahogando a todos.");
    else if (winner == 10) printf("%s", "Un llanto enganoso\n   termino en masacre.");
    else if (winner == 11) printf("%s", "Una trampa de la que\n   nunca despertara.");
    else printf("%s", "Victoria absoluta.");
    printf("\"\n\n\n");
    printf("   START: Menu Principal\n");
}

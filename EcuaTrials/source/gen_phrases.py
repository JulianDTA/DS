def get_victory_phrase(winner, loser):
    # Some specific interactions:
    if winner == 0 and loser == 7: # Cantuna vs Cura
        return "El oro del diablo supera\\n   a la magia oscura."
    if winner == 8 and loser == 9: # Chuzalongo vs Llorona
        return "El paramo no tiene\\n   piedad de las lagrimas."
    if winner == 9 and loser == 10: # Llorona vs Guagua Auca
        return "Un bebe mas arrastrado\\n   al fondo del rio..."
    if winner == 4 and loser == 1: # Dama Tapada vs Tin Tin
        return "El seductor cayo\\n   en la trampa mortal."
    if winner == 3 and loser == 7: # Padre Almeida vs Cura sin Cabeza
        return "Almeida seguira bebiendo;\\n   el otro seguira penando."
    if winner == 6 and loser == 0: # Gallo vs Cantuna
        return "La Catedral impone\\n   su ley sobre San Francisco."
    if winner == 5 and loser == 9: # Maria Angula vs Llorona
        return "Tus llantos no callaran\\n   mis gritos de culpa!"
    if winner == 10 and loser == 11: # Guagua Auca vs Viuda Tamarindo
        return "Un demonio pequenito\\n   gano a la tentacion."
    if winner == 2 and loser == 5: # Tunda vs Maria Angula
        return "La nina traviesa termino\\n   entundada en el manglar."
    if winner == 11 and loser == 3: # Viuda vs Padre Almeida
        return "La farra termino bajo\\n   el arbol de tamarindo."
    
    # Generic by role or character if no specific match
    roles = {
        0: "La arquitectura perfecta\\n   nunca se derrumba.", # Cantuna
        1: "Una travesura rapida\\n   fue mas que suficiente.", # Tin Tin
        2: "Nadie escapa vivo de\\n   los manglares...", # Tunda
        3: "Hasta la vuelta, senor!\\n   Y a seguir bebiendo.", # Padre Almeida
        4: "El terror absoluto\\n   paralizo al oponente.", # Dama Tapada
        5: "Devuelveme mis tripas!\\n   La venganza esta servida.", # Maria
        6: "Un canto de victoria\\n   resuena en la plaza.", # Gallo
        7: "La magia de ultratumba\\n   consumio su alma.", # Cura
        8: "Fuerza bruta y salvaje\\n   sin contemplaciones.", # Chuzalongo
        9: "Tanto dolor y pena\\n   terminan ahogando a todos.", # Llorona
        10: "Un llanto enganoso\\n   termino en masacre.", # Guagua
        11: "Una trampa de la que\\n   nunca despertara." # Viuda
    }
    return roles[winner]

with open("generate_phrases.c", "w") as f:
    f.write("static void print_match_result(int winner, int loser, bool player_won) {\n")
    f.write('    printf("\\n\\n\\n");\n')
    f.write('    if (player_won) {\n')
    f.write('        printf("   FELICIDADES!\\n\\n");\n')
    f.write('        printf("   %s ha vencido\\n", NOMBRES_PERSONAJES[winner]);\n')
    f.write('        printf("   a %s!\\n\\n", NOMBRES_PERSONAJES[loser]);\n')
    f.write('    } else {\n')
    f.write('        printf("   HAS CAIDO...\\n\\n");\n')
    f.write('        printf("   %s fue derrotado\\n", NOMBRES_PERSONAJES[loser]);\n')
    f.write('        printf("   por %s.\\n\\n", NOMBRES_PERSONAJES[winner]);\n')
    f.write('    }\n')
    
    f.write('    printf("   \\"");\n')
    
    f.write("    if (winner == 0 && loser == 7) printf(\"%s\", \"El oro del diablo supera\\n   a la magia oscura.\");\n")
    f.write("    else if (winner == 8 && loser == 9) printf(\"%s\", \"El paramo no tiene\\n   piedad de las lagrimas.\");\n")
    f.write("    else if (winner == 9 && loser == 10) printf(\"%s\", \"Un bebe mas arrastrado\\n   al fondo del rio...\");\n")
    f.write("    else if (winner == 4 && loser == 1) printf(\"%s\", \"El seductor cayo\\n   en la trampa mortal.\");\n")
    f.write("    else if (winner == 3 && loser == 7) printf(\"%s\", \"Almeida seguira bebiendo;\\n   el otro seguira penando.\");\n")
    f.write("    else if (winner == 6 && loser == 0) printf(\"%s\", \"La Catedral impone\\n   su ley sobre San Francisco.\");\n")
    f.write("    else if (winner == 5 && loser == 9) printf(\"%s\", \"Tus llantos no callaran\\n   mis gritos de culpa!\");\n")
    f.write("    else if (winner == 10 && loser == 11) printf(\"%s\", \"Un demonio pequenito\\n   gano a la tentacion.\");\n")
    f.write("    else if (winner == 2 && loser == 5) printf(\"%s\", \"La nina traviesa termino\\n   entundada en el manglar.\");\n")
    f.write("    else if (winner == 11 && loser == 3) printf(\"%s\", \"La farra termino bajo\\n   el arbol de tamarindo.\");\n")
    
    for i in range(12):
        f.write(f"    else if (winner == {i}) printf(\"%s\", \"{get_victory_phrase(i, -1)}\");\n")
        
    f.write("    else printf(\"%s\", \"Victoria absoluta.\");\n")
    
    f.write('    printf("\\"\\n\\n\\n");\n')
    f.write('    printf("   START: Menu Principal\\n");\n')
    f.write("}\n")
    

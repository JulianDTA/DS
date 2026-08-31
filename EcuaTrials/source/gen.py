import os
from cards_data import characters

# Balance check: make sure every deck has exactly 28 cards
for char in characters:
    total = sum(c[7] for c in char["cards"])
    while total > 28:
        for c in char["cards"]:
            if c[7] > 1:
                lst = list(c)
                lst[7] -= 1
                char["cards"][char["cards"].index(c)] = tuple(lst)
                break
        total = sum(c[7] for c in char["cards"])
    while total < 28:
        lst = list(char["cards"][0])
        lst[7] += 1
        char["cards"][0] = tuple(lst)
        total = sum(c[7] for c in char["cards"])

with open("generate_cards.c", "w") as f:
    f.write('#include "card.h"\n\n')
    
    # Write arrays
    for char in characters:
        f.write(f"// MAZO DE {char['name']}\n")
        f.write(f"const CardData CARTAS_{char['id']}[] = {{\n")
        card_id = 0
        for c in char["cards"]:
            for i in range(c[7]):
                lore = c[6]
                if len(lore) < 3: lore.append("")
                if len(lore) < 3: lore.append("")
                f.write(f'    {{{card_id}, "{c[0]}", {c[1]}, {c[2]}, {c[3]}, {c[4]}, {c[5]}, "{lore[0]}", "{lore[1]}", "{lore[2]}"}},\n')
                card_id += 1
        f.write("};\n")
        f.write(f"const int {char['id']}_DECK_SIZE = 28;\n\n")
        
with open("generate_cards.h", "w") as f:
    for char in characters:
        f.write(f"extern const CardData CARTAS_{char['id']}[];\n")
        f.write(f"extern const int {char['id']}_DECK_SIZE;\n")

with open("generate_game_arrays.txt", "w") as f:
    names = ", ".join(f'"{c["name"]}"' for c in characters)
    f.write(f"static const char* NOMBRES_PERSONAJES[] = {{{names}}};\n\n")
    
    f.write("static const CardData* get_deck_for_char(int id) {\n    switch(id) {\n")
    for idx, c in enumerate(characters):
        f.write(f"        case {idx}: return CARTAS_{c['id']};\n")
    f.write("        default: return CARTAS_CANTUNA;\n    }\n}\n\n")
    
    f.write("static int get_deck_size_for_char(int id) {\n    switch(id) {\n")
    for idx, c in enumerate(characters):
        f.write(f"        case {idx}: return {c['id']}_DECK_SIZE;\n")
    f.write("        default: return CANTUNA_DECK_SIZE;\n    }\n}\n\n")
    
    for idx, c in enumerate(characters):
        f.write(f"case {idx}:\n")
        f.write(f"    printf(\"   ========================\\n\");\n")
        f.write(f"    printf(\"   %s\\n\", NOMBRES_PERSONAJES[{idx}]);\n")
        f.write(f"    printf(\"   ========================\\n\\n\");\n")
        f.write(f"    printf(\"   Rol: %s\\n\", \"{c['role']}\");\n")
        f.write(f"    printf(\"   %s\\n\", \"{c['desc'][0]}\");\n")
        f.write(f"    printf(\"   %s\\n\", \"{c['desc'][1]}\");\n")
        f.write(f"    printf(\"   %s\\n\", \"{c['desc'][2]}\");\n")
        f.write("    break;\n")

print("Generated code successfully.")

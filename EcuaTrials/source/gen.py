import os
import textwrap
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

with open("source/card.c", "w") as f:
    f.write('#include "card.h"\n\n')
    
    # Write arrays
    for char in characters:
        f.write(f"// MAZO DE {char['name']}\n")
        f.write(f"const CardData CARTAS_{char['id']}[] = {{\n")
        card_id = 0
        for c in char["cards"]:
            for i in range(c[7]):
                lore_raw = " ".join(c[6])
                # Auto-wrap to 13 chars
                lore = textwrap.wrap(lore_raw, width=13)
                lores_str = []
                for j in range(7):
                    if j < len(lore):
                        lores_str.append(f'"{lore[j]}"')
                    else:
                        lores_str.append('NULL')
                lore_csv = ", ".join(lores_str)
                f.write(f'    {{{card_id}, "{c[0]}", {c[1]}, {c[2]}, {c[3]}, {c[4]}, {c[5]}, {lore_csv}}},\n')
                card_id += 1
        f.write("};\n")
        f.write(f"const int {char['id']}_DECK_SIZE = 28;\n\n")

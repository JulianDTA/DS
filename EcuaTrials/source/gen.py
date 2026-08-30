import os

characters = [
    {
        "id": "CANTUNA", "name": "Cantuna", "role": "TANQUE",
        "desc": ["Constructor legendario", "Pacto con el diablo", "Escudos fuertes"],
        "cards": [
            ("Ladrillazo", "FX_ATTACK", 3, 0, 0, 0, ["Arroja un ladrillo", "Dano: 3"], 3),
            ("Golpe de Piedra", "FX_ATTACK", 2, 0, 0, 0, ["Piedra tallada", "Dano: 2"], 3),
            ("Avalancha", "FX_ATTACK", 5, 0, 0, 0, ["Poder del Pichincha", "Dano: 5"], 2),
            ("Muro de Piedra", "FX_SHIELD", 0, 2, 0, 0, ["Muro de iglesia", "Escudo: 2"], 3),
            ("Fortaleza", "FX_SHIELD", 0, 3, 0, 0, ["Ni el diablo pasa", "Escudo: 3"], 3),
            ("Descanso", "FX_HEAL", 0, 0, 2, 0, ["Descansa un rato", "Cura: 2 HP"], 2),
            ("Pacto Diabolico", "FX_HEAL", 0, 0, 4, 0, ["El diablo ayuda", "Cura: 4 HP"], 2),
            ("Planos Secretos", "FX_DRAW", 0, 0, 0, 2, ["Nuevas ideas", "Roba: 2"], 2),
            ("Inspiracion", "FX_DRAW | FX_PLAY_AGAIN", 0, 0, 0, 1, ["Ideas geniales", "Roba: 1 + Juega otra"], 2),
            ("Contraataque", "FX_ATTACK | FX_SHIELD", 2, 1, 0, 0, ["Golpea y cubre", "Dano:2 Escudo:1"], 2),
            ("Furia Constructor", "FX_ATTACK | FX_PLAY_AGAIN", 2, 0, 0, 0, ["Construye rapido", "Dano:2 + Juega otra"], 2),
            ("Bendicion Oscura", "FX_HEAL | FX_DRAW", 0, 0, 2, 1, ["Trato oscuro", "Cura:2 Roba:1"], 2)
        ]
    },
    {
        "id": "TINTIN", "name": "El Tin Tin", "role": "AGRESOR",
        "desc": ["Duende travieso", "Aparece en las sombras", "Cadenas de combos"],
        "cards": [
            ("Travesura", "FX_ATTACK", 2, 0, 0, 0, ["Esconde tus cosas", "Dano: 2"], 4),
            ("Sombrerazo", "FX_ATTACK", 3, 0, 0, 0, ["Sombrero gigante", "Dano: 3"], 3),
            ("Emboscada", "FX_ATTACK", 4, 0, 0, 0, ["Sale de la nada", "Dano: 4"], 3),
            ("Escondite", "FX_SHIELD", 0, 1, 0, 0, ["Se esconde", "Escudo: 1"], 3),
            ("Siesta Maliciosa", "FX_HEAL", 0, 0, 2, 0, ["Planear la proxima", "Cura: 2 HP"], 2),
            ("Robo de Bolsillos", "FX_DRAW", 0, 0, 0, 2, ["Manos rapidas", "Roba: 2"], 3),
            ("Agilidad", "FX_DRAW | FX_PLAY_AGAIN", 0, 0, 0, 1, ["Rapido!", "Roba:1 + Juega otra"], 4),
            ("Golpe Fugaz", "FX_ATTACK | FX_PLAY_AGAIN", 2, 0, 0, 0, ["Golpea y se va", "Dano:2 + Juega otra"], 3),
            ("Ataque Sorpresa", "FX_ATTACK | FX_DRAW", 3, 0, 0, 1, ["Por la espalda", "Dano:3 Roba:1"], 3)
        ]
    },
    {
        "id": "TUNDA", "name": "La Tunda", "role": "CONTROL",
        "desc": ["Bruja del manglar", "Pierna de molinillo", "Curacion y drenaje"],
        "cards": [
            ("Zarpazo", "FX_ATTACK", 3, 0, 0, 0, ["Mano de garra", "Dano: 3"], 3),
            ("Molinillazo", "FX_ATTACK", 4, 0, 0, 0, ["Golpe de pata", "Dano: 4"], 3),
            ("Niebla Espesa", "FX_SHIELD", 0, 2, 0, 0, ["Niebla protectora", "Escudo: 2"], 4),
            ("Camarones Magicos", "FX_HEAL", 0, 0, 2, 0, ["Camarones frescos", "Cura: 2 HP"], 4),
            ("Ritual Sanacion", "FX_HEAL", 0, 0, 4, 0, ["Cantos ancestrales", "Cura: 4 HP"], 4),
            ("Susurros", "FX_DRAW", 0, 0, 0, 2, ["Misterios", "Roba: 2"], 2),
            ("Encantamiento", "FX_DRAW | FX_PLAY_AGAIN", 0, 0, 0, 1, ["Hipnosis", "Roba:1 + Juega otra"], 2),
            ("Drenar Vida", "FX_ATTACK | FX_HEAL", 2, 0, 2, 0, ["Absorbe energia", "Dano:2 Cura:2"], 3),
            ("Maldicion", "FX_ATTACK | FX_SHIELD", 3, 1, 0, 0, ["Mal de ojo", "Dano:3 Escudo:1"], 3)
        ]
    },
    {
        "id": "ALMEIDA", "name": "Padre Almeida", "role": "COMBO",
        "desc": ["Sacerdote rebelde", "Sale de farra", "Mucho robo de cartas"],
        "cards": [
            ("Guitarrazo", "FX_ATTACK", 2, 0, 0, 0, ["Golpe musical", "Dano: 2"], 4),
            ("Hasta la vuelta", "FX_ATTACK", 4, 0, 0, 0, ["Senor, hasta la vuelta", "Dano: 4"], 3),
            ("Salto del Muro", "FX_ATTACK | FX_PLAY_AGAIN", 2, 0, 0, 0, ["Se escapa", "Dano:2 + Juega otra"], 4),
            ("Habito Protector", "FX_SHIELD", 0, 2, 0, 0, ["Proteccion sagrada", "Escudo: 2"], 4),
            ("Arrepentimiento", "FX_HEAL", 0, 0, 3, 0, ["Reza por perdon", "Cura: 3 HP"], 3),
            ("Farra Nocturna", "FX_DRAW", 0, 0, 0, 2, ["Mas diversion", "Roba: 2"], 4),
            ("Brindis", "FX_HEAL | FX_DRAW", 0, 0, 2, 1, ["Salud!", "Cura:2 Roba:1"], 3),
            ("Pecado y Culpa", "FX_ATTACK | FX_SHIELD", 3, 1, 0, 0, ["Doble moral", "Dano:3 Escudo:1"], 3)
        ]
    },
    {
        "id": "DAMATAPADA", "name": "Dama Tapada", "role": "TERROR",
        "desc": ["Mujer misteriosa", "Rostro calaverico", "Debuffs y miedo"],
        "cards": [
            ("Susto Mortal", "FX_ATTACK", 4, 0, 0, 0, ["Muestra el rostro", "Dano: 4"], 4),
            ("Perfume Barato", "FX_ATTACK", 2, 0, 0, 0, ["Aroma mareador", "Dano: 2"], 4),
            ("Velo de Viuda", "FX_SHIELD", 0, 3, 0, 0, ["Oculta su ser", "Escudo: 3"], 4),
            ("Seduccion", "FX_DRAW | FX_PLAY_AGAIN", 0, 0, 0, 1, ["Atrae victimas", "Roba:1 + Juega otra"], 4),
            ("Beso Frío", "FX_ATTACK | FX_HEAL", 3, 0, 2, 0, ["Drena la vida", "Dano:3 Cura:2"], 4),
            ("Ilusion", "FX_SHIELD | FX_PLAY_AGAIN", 0, 1, 0, 0, ["Aparece y desaparece", "Escudo:1 + Juega"], 4),
            ("Rostro Calavera", "FX_ATTACK | FX_DRAW", 5, 0, 0, 1, ["Terror absoluto", "Dano:5 Roba:1"], 4)
        ]
    },
    {
        "id": "MARIANGULA", "name": "Maria Angula", "role": "AGRESOR",
        "desc": ["Nina golosa", "Robo tripas del muerto", "Ataques freneticos"],
        "cards": [
            ("Robo de Tripas", "FX_ATTACK", 5, 0, 0, 0, ["Profana la tumba", "Dano: 5"], 4),
            ("Panza Llena", "FX_HEAL", 0, 0, 3, 0, ["Come demasiado", "Cura: 3 HP"], 4),
            ("Sopa de Menudencias", "FX_ATTACK | FX_PLAY_AGAIN", 2, 0, 0, 0, ["Cocina el mal", "Dano:2 + Juega otra"], 5),
            ("Miedo a la Noche", "FX_SHIELD", 0, 2, 0, 0, ["Se esconde aterrorizada", "Escudo: 2"], 4),
            ("Devuelveme mis tripas!", "FX_ATTACK | FX_DRAW", 4, 0, 0, 1, ["El muerto reclama", "Dano:4 Roba:1"], 4),
            ("Hambre Insaciable", "FX_DRAW | FX_PLAY_AGAIN", 0, 0, 0, 1, ["Quiere mas", "Roba:1 + Juega otra"], 4),
            ("Pesadilla", "FX_ATTACK | FX_SHIELD", 3, 2, 0, 0, ["El terror no la deja", "Dano:3 Escudo:2"], 3)
        ]
    },
    {
        "id": "GALLO", "name": "Gallo Catedral", "role": "EQUILIBRADO",
        "desc": ["Gallo de oro", "Canta en la iglesia", "Danio y velocidad"],
        "cards": [
            ("Picotazo", "FX_ATTACK", 3, 0, 0, 0, ["Pico de oro", "Dano: 3"], 5),
            ("Canto Matutino", "FX_HEAL | FX_DRAW", 0, 0, 2, 1, ["Amanecer", "Cura:2 Roba:1"], 4),
            ("Alas de Bronce", "FX_SHIELD", 0, 3, 0, 0, ["Escudo metalico", "Escudo: 3"], 4),
            ("Vuelo Corto", "FX_DRAW | FX_PLAY_AGAIN", 0, 0, 0, 1, ["Esquiva todo", "Roba:1 + Juega otra"], 4),
            ("Grito Ensordecedor", "FX_ATTACK | FX_PLAY_AGAIN", 2, 0, 0, 0, ["Despierta a todos", "Dano:2 + Juega otra"], 4),
            ("Estatua Posesa", "FX_ATTACK | FX_SHIELD", 4, 2, 0, 0, ["Toma vida", "Dano:4 Escudo:2"], 4),
            ("Pluma Dorada", "FX_HEAL", 0, 0, 4, 0, ["Brillo sanador", "Cura: 4 HP"], 3)
        ]
    },
    {
        "id": "CURA", "name": "Cura sin Cabeza", "role": "MAGIA",
        "desc": ["Sacerdote maldito", "No tiene cabeza", "Magia oscura pura"],
        "cards": [
            ("Llama Negra", "FX_ATTACK", 6, 0, 0, 0, ["Fuego del purgatorio", "Dano: 6"], 3),
            ("Sermon Mudo", "FX_ATTACK | FX_PLAY_AGAIN", 2, 0, 0, 0, ["Habla sin voz", "Dano:2 + Juega"], 4),
            ("Aparicion", "FX_SHIELD", 0, 4, 0, 0, ["No lo puedes tocar", "Escudo: 4"], 3),
            ("Misa de Medianoche", "FX_HEAL", 0, 0, 5, 0, ["Ritual oscuro", "Cura: 5 HP"], 3),
            ("Busqueda de Cabeza", "FX_DRAW", 0, 0, 0, 3, ["Roba muchas cartas", "Roba: 3 cartas"], 3),
            ("Condena", "FX_ATTACK | FX_SHIELD", 4, 2, 0, 0, ["El juicio final", "Dano:4 Escudo:2"], 4),
            ("Aura Espectral", "FX_HEAL | FX_DRAW", 0, 0, 2, 1, ["Espiritu inquieto", "Cura:2 Roba:1"], 4),
            ("Levitacion", "FX_DRAW | FX_PLAY_AGAIN", 0, 0, 0, 1, ["Flota", "Roba:1 + Juega otra"], 4)
        ]
    },
    {
        "id": "CHUZALONGO", "name": "El Chuzalongo", "role": "SALVAJE",
        "desc": ["Criatura del Paramo", "Agresividad pura", "Nula defensa"],
        "cards": [
            ("Mordida Salvaje", "FX_ATTACK", 5, 0, 0, 0, ["Muerde fuerte", "Dano: 5"], 6),
            ("Garras Paramo", "FX_ATTACK", 4, 0, 0, 0, ["Arana feo", "Dano: 4"], 5),
            ("Piel Gruesa", "FX_SHIELD", 0, 1, 0, 0, ["Poco escudo", "Escudo: 1"], 3),
            ("Instinto Animal", "FX_DRAW | FX_PLAY_AGAIN", 0, 0, 0, 1, ["Actua rapido", "Roba:1 + Juega otra"], 4),
            ("Furia Ciega", "FX_ATTACK | FX_PLAY_AGAIN", 3, 0, 0, 0, ["Golpea sin ver", "Dano:3 + Juega"], 4),
            ("Carne Cruda", "FX_HEAL", 0, 0, 2, 0, ["Se alimenta", "Cura: 2 HP"], 3),
            ("Aullido", "FX_ATTACK | FX_DRAW", 4, 0, 0, 1, ["Llama a la manada", "Dano:4 Roba:1"], 3)
        ]
    },
    {
        "id": "LLORONA", "name": "La Llorona", "role": "TRISTEZA",
        "desc": ["Madre en pena", "Busca a sus hijos", "Mucha curacion"],
        "cards": [
            ("Mis Hijos!", "FX_ATTACK", 3, 0, 0, 0, ["Grito agudo", "Dano: 3"], 4),
            ("Llanto Incesante", "FX_HEAL", 0, 0, 4, 0, ["Llora y sana", "Cura: 4 HP"], 5),
            ("Rio Desbordado", "FX_ATTACK | FX_SHIELD", 3, 2, 0, 0, ["Agua violenta", "Dano:3 Escudo:2"], 4),
            ("Manto Blanco", "FX_SHIELD", 0, 3, 0, 0, ["Vestido espectral", "Escudo: 3"], 4),
            ("Desesperacion", "FX_DRAW | FX_PLAY_AGAIN", 0, 0, 0, 1, ["Actua sin pensar", "Roba:1 + Juega"], 4),
            ("Ahogo", "FX_ATTACK | FX_HEAL", 4, 0, 2, 0, ["Drena el oxigeno", "Dano:4 Cura:2"], 4),
            ("Lágrimas", "FX_DRAW", 0, 0, 0, 2, ["Penas pasadas", "Roba: 2"], 3)
        ]
    },
    {
        "id": "GUAGUAAUCA", "name": "Guagua Auca", "role": "SORPRESA",
        "desc": ["Bebe fantasma", "Demonio enganoso", "Robo y dano"],
        "cards": [
            ("Lloriqueo", "FX_ATTACK", 2, 0, 0, 0, ["Llora para enganar", "Dano: 2"], 5),
            ("Dientes de Diablo", "FX_ATTACK", 5, 0, 0, 0, ["Muerde cuando lo abrazan", "Dano: 5"], 4),
            ("Panales", "FX_SHIELD", 0, 2, 0, 0, ["Parece inofensivo", "Escudo: 2"], 4),
            ("Sorpresa Maligna", "FX_ATTACK | FX_PLAY_AGAIN", 3, 0, 0, 0, ["Susto", "Dano:3 + Juega"], 5),
            ("Risa Macabra", "FX_DRAW", 0, 0, 0, 2, ["Se burla", "Roba: 2"], 4),
            ("Inocencia Fingida", "FX_HEAL | FX_DRAW", 0, 0, 3, 1, ["Te da pena", "Cura:3 Roba:1"], 4),
            ("Mordisco", "FX_ATTACK | FX_SHIELD", 2, 2, 0, 0, ["Golpea de cerca", "Dano:2 Escudo:2"], 2)
        ]
    },
    {
        "id": "VIUDA", "name": "Viuda Tamarindo", "role": "TRAMPA",
        "desc": ["Aparece en Guayaquil", "Debajo del tamarindo", "Control total"],
        "cards": [
            ("Seduccion Oscura", "FX_ATTACK | FX_HEAL", 4, 0, 3, 0, ["Te enamora y te mata", "Dano:4 Cura:3"], 4),
            ("Abrazo de Muerte", "FX_ATTACK", 5, 0, 0, 0, ["Te asfixia", "Dano: 5"], 4),
            ("Sombra del Arbol", "FX_SHIELD", 0, 4, 0, 0, ["El tamarindo la protege", "Escudo: 4"], 4),
            ("Velo Negro", "FX_DRAW | FX_PLAY_AGAIN", 0, 0, 0, 1, ["Magia negra", "Roba:1 + Juega"], 4),
            ("Borracho Perdido", "FX_ATTACK | FX_PLAY_AGAIN", 2, 0, 0, 0, ["Engana a sus victimas", "Dano:2 + Juega"], 4),
            ("Pasion Falsa", "FX_HEAL", 0, 0, 5, 0, ["Beso curativo", "Cura: 5"], 4),
            ("Aroma Dulce", "FX_DRAW", 0, 0, 0, 2, ["Atrae a incautos", "Roba: 2"], 4)
        ]
    }
]

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

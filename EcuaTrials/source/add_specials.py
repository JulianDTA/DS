import sys
sys.path.append('source')
from cards_data import characters
import pprint

# To balance the deck to 28 after adding 2 new cards (qty 1 each), 
# we need to reduce the quantity of two existing basic cards by 1.
# Usually cards[0] and cards[2] have 5 copies. We'll drop them to 4.

new_specials = {
    0: [ # Cantuna
        ("Pacto Enganoso", "FX_STEAL_HAND | FX_HEAL", 0, 0, 3, 0, ["El diablo cobra", "su deuda en el rival.", "[C: 3] [Roba de mano]"], 1),
        ("Cimiento Solido", "FX_STEAL_DISCARD | FX_SHIELD", 0, 4, 0, 0, ["Usa los restos para", "blindarse por completo.", "[E: 4] [Roba descarte]"], 1)
    ],
    1: [ # Tin Tin
        ("Sombrero Magico", "FX_STEAL_DECK | FX_DRAW | FX_PLAY_AGAIN", 0, 0, 0, 2, ["Saca sorpresas", "interminables.", "[R: 2] [Roba mazo] [+Juega]"], 1),
        ("Asalto Fugaz", "FX_STEAL_HAND | FX_ATTACK", 3, 0, 0, 0, ["Te golpea y te deja", "sin opciones.", "[D: 3] [Roba de mano]"], 1)
    ],
    2: [ # Tunda
        ("Maldicion del Manglar", "FX_STEAL_HAND | FX_STEAL_DISCARD", 0, 0, 0, 0, ["Pierdes todo", "lo que tenias.", "[Roba mano y descarte]"], 1),
        ("Ilusion Maternal", "FX_STEAL_DECK | FX_HEAL", 0, 0, 3, 0, ["Finge ser tu madre", "para robar tu futuro.", "[C: 3] [Roba mazo rival]"], 1)
    ],
    3: [ # Almeida
        ("Escape Milagroso", "FX_STEAL_HAND | FX_DRAW", 0, 0, 0, 2, ["Esquiva tu ataque y", "huye con ventaja.", "[R: 2] [Roba de mano]"], 1),
        ("Trago Robado", "FX_STEAL_DISCARD | FX_HEAL | FX_PLAY_AGAIN", 0, 0, 2, 0, ["Bebe de la botella", "que creias vacia.", "[C: 2] [Roba descarte] [+J]"], 1)
    ],
    4: [ # Dama Tapada
        ("Perfume Letal", "FX_STEAL_DECK | FX_ATTACK", 4, 0, 0, 0, ["El olor a muerte", "arruina tu destino.", "[D: 4] [Roba mazo rival]"], 1),
        ("Mirada al Abismo", "FX_STEAL_HAND | FX_STEAL_DECK", 0, 0, 0, 0, ["El panico te", "hace perder la cabeza.", "[Roba mano y mazo]"], 1)
    ],
    5: [ # Maria Angula
        ("Sopa de Robos", "FX_STEAL_DISCARD | FX_STEAL_HAND", 0, 0, 0, 0, ["Saca ingredientes", "de donde sea.", "[Roba mano y descarte]"], 1),
        ("Berrinche Mortal", "FX_STEAL_DECK | FX_ATTACK | FX_PLAY_AGAIN", 2, 0, 0, 0, ["Destruye todo", "a su paso.", "[D: 2] [Roba mazo] [+J]"], 1)
    ],
    6: [ # Gallo
        ("Canto Hipnotico", "FX_STEAL_HAND | FX_SHIELD", 0, 3, 0, 0, ["Te aturde mientras", "se protege.", "[E: 3] [Roba de mano]"], 1),
        ("Brillo Cegador", "FX_STEAL_DISCARD | FX_DRAW | FX_PLAY_AGAIN", 0, 0, 0, 1, ["Resplandece y toma", "la iniciativa.", "[R: 1] [Roba descarte] [+J]"], 1)
    ],
    7: [ # Cura
        ("Fuego del Purgatorio", "FX_STEAL_DECK | FX_ATTACK", 5, 0, 0, 0, ["Quema tu esperanza.", "", "[D: 5] [Roba mazo rival]"], 1),
        ("Exorcismo Inverso", "FX_STEAL_HAND | FX_HEAL", 0, 0, 4, 0, ["Te drena el alma.", "", "[C: 4] [Roba de mano]"], 1)
    ],
    8: [ # Chuzalongo
        ("Ataque Furtivo", "FX_STEAL_HAND | FX_ATTACK", 4, 0, 0, 0, ["Muerde y se roba", "lo que caiga.", "[D: 4] [Roba de mano]"], 1),
        ("Carrona", "FX_STEAL_DISCARD | FX_HEAL | FX_DRAW", 0, 0, 2, 1, ["Se alimenta de tus", "restos.", "[C: 2] [R: 1] [Roba desc]"], 1)
    ],
    9: [ # Llorona
        ("Llanto Ahogado", "FX_STEAL_DECK | FX_SHIELD", 0, 4, 0, 0, ["Sus lagrimas forman", "una barrera.", "[E: 4] [Roba mazo rival]"], 1),
        ("Arrastrar al Fondo", "FX_STEAL_DISCARD | FX_ATTACK | FX_HEAL", 2, 0, 2, 0, ["Te hunde con ella.", "", "[D: 2] [C: 2] [Roba desc]"], 1)
    ],
    10: [ # Guagua Auca
        ("Berrinche Infernal", "FX_STEAL_DECK | FX_STEAL_DISCARD", 0, 0, 0, 0, ["Un demonio desatado", "robando por doquier.", "[Roba mazo y descarte]"], 1),
        ("Muerde Dedos", "FX_STEAL_HAND | FX_ATTACK | FX_PLAY_AGAIN", 2, 0, 0, 0, ["Engana y ataca", "muy rapido.", "[D: 2] [Roba mano] [+J]"], 1)
    ],
    11: [ # Viuda
        ("Seduccion Oscura", "FX_STEAL_DECK | FX_STEAL_HAND", 0, 0, 0, 0, ["El engaño perfecto.", "", "[Roba mazo y mano]"], 1),
        ("Asfixia", "FX_STEAL_DISCARD | FX_ATTACK | FX_PLAY_AGAIN", 3, 0, 0, 0, ["Te roba el aire y", "tus recuerdos.", "[D: 3] [Roba desc] [+J]"], 1)
    ]
}

for char in characters:
    char_id = characters.index(char)
    
    # Reducir dos cartas basicas de 5 a 4
    for i in range(len(char['cards'])):
        if char['cards'][i][7] == 5:
            lst = list(char['cards'][i])
            lst[7] = 4
            char['cards'][i] = tuple(lst)
            break
            
    for i in range(len(char['cards'])-1, -1, -1):
        if char['cards'][i][7] == 5:
            lst = list(char['cards'][i])
            lst[7] = 4
            char['cards'][i] = tuple(lst)
            break
            
    # Agregar las 2 nuevas especiales (cada una de qty 1)
    for new_card in new_specials[char_id]:
        char['cards'].append(new_card)

with open('source/cards_data.py', 'w') as f:
    f.write('characters = \\\n')
    f.write(pprint.pformat(characters, sort_dicts=False))
    f.write('\n')


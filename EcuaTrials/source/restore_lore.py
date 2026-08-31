lores = {
    0: [
        "Cuenta la leyenda que",
        "Cantuna hizo un pacto con",
        "el diablo para construir",
        "la Iglesia de San Francisco",
        "en una sola noche.",
        "",
        "Pero el astuto constructor",
        "quito un ladrillo antes de",
        "amanecer, y el diablo no",
        "pudo reclamar su alma.",
        "",
        "Rol: TANQUE",
        "Escudos fuertes, golpes",
        "devastadores."
    ],
    1: [
        "Un duende travieso de la",
        "costa ecuatoriana.",
        "Usa un sombrero enorme y",
        "aparece en las sombras",
        "para asustar a la gente.",
        "",
        "Le encanta esconder cosas,",
        "hacer nudos en el cabello",
        "y robar de los bolsillos",
        "con sus manos rapidas.",
        "",
        "Rol: AGRESOR",
        "Ataques rapidos, combos",
        "impredecibles."
    ],
    2: [
        "Espiritu del manglar.",
        "Tiene una pierna humana",
        "y otra de molinillo.",
        "",
        "Se disfraza de un ser",
        "querido para atraer a",
        "los ninos al bosque",
        "ofreciendo camarones.",
        "Asi los hipnotiza.",
        "",
        "Rol: CONTROL",
        "Curacion poderosa y",
        "drenaje de vida."
    ],
    3: [
        "Un sacerdote franciscano",
        "que escapaba del convento",
        "para irse de farra.",
        "",
        "Pisaba la estatua de",
        "Cristo, quien le pregunto:",
        "Hasta cuando Padre",
        "Almeida? El respondio:",
        "Hasta la vuelta, Senor.",
        "",
        "Rol: COMBO",
        "Poca defensa pero",
        "mucho robo de cartas."
    ],
    4: [
        "Misteriosa mujer que",
        "camina por Guayaquil a",
        "la medianoche.",
        "Su perfume embriagador",
        "atrae a los hombres.",
        "",
        "Al quitarse el velo,",
        "muestra su craneo y",
        "un olor a muerte que",
        "paraliza a sus victimas.",
        "",
        "Rol: TERROR",
        "Debuffs, escudos y",
        "dano masivo."
    ],
    5: [
        "Nina muy golosa.",
        "Su madre le pidio",
        "comprar tripas, pero",
        "se gasto el dinero.",
        "",
        "Para enganarla, robo",
        "las tripas de un muerto.",
        "El espiritu la busco",
        "gritando por sus tripas.",
        "",
        "Rol: AGRESOR",
        "Ataques freneticos y",
        "comportamiento salvaje."
    ],
    6: [
        "El gallo de bronce de",
        "la Catedral cobro vida",
        "para darle una leccion",
        "a Don Ramon Ayala,",
        "un hombre jactancioso.",
        "",
        "Despues de que lo",
        "insultara repetidas veces,",
        "el ave dorada bajo a",
        "picotearlo sin piedad.",
        "",
        "Rol: EQUILIBRADO",
        "Ataques desde el aire,",
        "buena curacion."
    ],
    7: [
        "El espectro de un",
        "sacerdote condenado",
        "a vagar sin su cabeza",
        "por sus terribles pecados.",
        "",
        "Su silueta oscura",
        "atormenta las calles,",
        "emanando un frio",
        "sobrenatural a su paso.",
        "",
        "Rol: MAGIA",
        "Dano magico norme,",
        "imposible de bloquear."
    ],
    8: [
        "Una criatura salvaje",
        "de los paramos andinos.",
        "Mitad nino, mitad bestia,",
        "protege a los animales.",
        "",
        "Tiene una agresividad",
        "desmedida y ataca con",
        "furia incontrolable a",
        "quien falte el respeto.",
        "",
        "Rol: SALVAJE",
        "Ataques brutales puros",
        "con nula defensa."
    ],
    9: [
        "El alma en pena de",
        "una mujer que perdio a",
        "su hijo en un rio.",
        "",
        "Vaga por las orillas",
        "llorando sin consuelo.",
        "Su inmenso dolor",
        "marchita las plantas y",
        "hiela la sangre.",
        "",
        "Rol: TRISTEZA",
        "Mucha curacion base y",
        "escudos impenetrables."
    ],
    10: [
        "El espiritu de un bebe",
        "no bautizado que fue",
        "abandonado. Su llanto",
        "despierta compasion.",
        "",
        "Pero cuando un viajero",
        "lo toma en sus brazos,",
        "el bebe muestra dientes",
        "de demonio y ataca.",
        "",
        "Rol: SORPRESA",
        "Robo de cartas",
        "y ataques enganosos."
    ],
    11: [
        "El fantasma de una",
        "mujer que ronda un",
        "antiguo tamarindo.",
        "",
        "Llora buscando consuelo,",
        "pero si alguien se le",
        "acerca, revela un rostro",
        "que provoca la locura.",
        "",
        "Rol: TRAMPA",
        "Drenaje de vida,",
        "ilusiones y control."
    ]
}

cases_code = ""
for i in range(12):
    cases_code += f"case {i}:\n"
    cases_code += f"    printf(\"   ========================\\n\");\n"
    cases_code += f"    printf(\"   %s\\n\", NOMBRES_PERSONAJES[{i}]);\n"
    cases_code += f"    printf(\"   ========================\\n\\n\");\n"
    for line in lores[i]:
        if len(line) > 28:
            print(f"ERROR TOO LONG: {line}")
        cases_code += f"    printf(\"   {line}\\n\");\n"
    cases_code += "    break;\n"

import re

with open('source/game.c', 'r') as f:
    code = f.read()

pattern = r'(case GAME_SELECT_CHAR:\n            printf\("\\n\\n"\);\n            switch \(gs->personaje_elegido\) \{\n)(.*?)(            \}\n            break;\n\n        case GAME_COMBAT:)'
code = re.sub(pattern, r'\g<1>' + cases_code.replace('\\', '\\\\') + r'\g<3>', code, flags=re.DOTALL)

with open('source/game.c', 'w') as f:
    f.write(code)

print("Lore successfully restored with correct line wrapping.")

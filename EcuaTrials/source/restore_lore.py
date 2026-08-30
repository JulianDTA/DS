import re

lores = {
    0: [
        "Cuenta la leyenda que Cantuna",
        "hizo un pacto con el diablo para",
        "construir la Iglesia de San",
        "Francisco en Quito en una sola",
        "noche.",
        "",
        "Pero el astuto constructor",
        "quito un ladrillo antes del",
        "amanecer, y el diablo no pudo",
        "reclamar su alma.",
        "",
        "Rol: TANQUE",
        "Escudos fuertes, golpes",
        "devastadores."
    ],
    1: [
        "Un duende travieso y escurridizo",
        "de la costa ecuatoriana.",
        "Usa un sombrero enorme y",
        "aparece en los caminos oscuros",
        "para asustar a los viajeros.",
        "",
        "Le encanta esconder cosas,",
        "hacer nudos en el cabello y",
        "robar de los bolsillos con",
        "sus manos rapidisimas.",
        "",
        "Rol: AGRESOR",
        "Ataques rapidos, cadenas",
        "de combos impredecibles."
    ],
    2: [
        "Espiritu femenino de los",
        "manglares de Esmeraldas.",
        "Tiene una pierna humana y",
        "otra de molinillo de madera.",
        "",
        "Se transforma en un ser",
        "querido para atraer a los",
        "ninos al bosque ofreciendoles",
        "camarones magicos, donde los",
        "hipnotiza ('entunda').",
        "",
        "Rol: CONTROL",
        "Curacion poderosa y",
        "drenaje de vida."
    ],
    3: [
        "Un sacerdote franciscano",
        "de Quito que escapaba de su",
        "convento por las noches para",
        "irse de farra y beber.",
        "",
        "Para salir, pisaba la estatua",
        "de Cristo, quien un dia le",
        "pregunto: 'Hasta cuando Padre",
        "Almeida?'. El respondio:",
        "'Hasta la vuelta, Senor'.",
        "",
        "Rol: COMBO",
        "Poca defensa pero",
        "mucho robo de cartas."
    ],
    4: [
        "Una misteriosa mujer que",
        "camina por las calles de",
        "Guayaquil pasada la medianoche.",
        "Exhala un perfume embriagador",
        "que atrae a los hombres.",
        "",
        "Al descubrirse el velo,",
        "muestra un rostro calaverico",
        "y un olor a muerte que paraliza",
        "de terror a sus victimas.",
        "",
        "Rol: TERROR",
        "Debuffs, escudos espectrales",
        "y dano masivo."
    ],
    5: [
        "Una nina muy golosa y",
        "mentirosa. Su madre le pidio",
        "comprar tripas, pero ella se",
        "gasto el dinero en dulces.",
        "",
        "Para enganarla, robo las",
        "tripas de un muerto fresco.",
        "Esa noche, el espiritu",
        "fue a buscarla gritando:",
        "'Devuelveme mis tripas!'",
        "",
        "Rol: AGRESOR",
        "Ataques freneticos y",
        "comportamiento salvaje."
    ],
    6: [
        "El gallo de bronce de la",
        "Catedral de Quito cobro vida",
        "para darle una leccion a Don",
        "Ramon Ayala, un hombre rico",
        "y muy jactancioso.",
        "",
        "Despues de que Don Ramon",
        "insultara al gallo repetidas",
        "veces, el ave dorada bajo",
        "a picotearlo sin piedad.",
        "",
        "Rol: EQUILIBRADO",
        "Ataques desde el aire,",
        "buena curacion."
    ],
    7: [
        "El espectro de un sacerdote",
        "condenado a vagar sin su",
        "cabeza por sus terribles",
        "pecados en vida.",
        "",
        "Su silueta oscura atormenta",
        "las calles empedradas de la",
        "sierra, emanando un frio",
        "sobrenatural a su paso.",
        "",
        "Rol: MAGIA",
        "Dano magico enorme,",
        "imposible de bloquear",
        "con escudos fisicos."
    ],
    8: [
        "Una criatura salvaje de",
        "los paramos andinos.",
        "Mitad nino, mitad bestia,",
        "protege celosamente a los",
        "animales salvajes.",
        "",
        "Tiene una agresividad",
        "desmedida y ataca con una",
        "furia incontrolable a quien",
        "falte el respeto a su hogar.",
        "",
        "Rol: SALVAJE",
        "Ataques brutales puros",
        "con nula defensa."
    ],
    9: [
        "El alma en pena de una",
        "mujer que perdio a su hijo",
        "en las aguas de un rio.",
        "",
        "Vaga por las orillas llorando",
        "desconsoladamente. Su dolor",
        "es tan grande que marchita",
        "las plantas y hiela la sangre",
        "de quien la escucha.",
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
        "lo toma en brazos para",
        "ayudarlo, el bebe muestra",
        "dientes de demonio y",
        "ataca sin piedad.",
        "",
        "Rol: SORPRESA",
        "Robo de cartas constante",
        "y ataques enganosos."
    ],
    11: [
        "El fantasma de una mujer",
        "que ronda un antiguo",
        "arbol de tamarindo en una",
        "hacienda costeña.",
        "",
        "Llora buscando consuelo,",
        "pero si alguien se le",
        "acerca, revela un rostro",
        "horrendo que provoca",
        "locura o la muerte.",
        "",
        "Rol: TRAMPA",
        "Drenaje de vida, ilusiones",
        "y control absoluto."
    ]
}

cases_code = ""
for i in range(12):
    cases_code += f"case {i}:\n"
    cases_code += f"    printf(\"   ========================\\n\");\n"
    cases_code += f"    printf(\"   %s\\n\", NOMBRES_PERSONAJES[{i}]);\n"
    cases_code += f"    printf(\"   ========================\\n\\n\");\n"
    for line in lores[i]:
        cases_code += f"    printf(\"   {line}\\n\");\n"
    cases_code += "    break;\n"

with open('source/game.c', 'r') as f:
    code = f.read()

pattern = r'(case GAME_SELECT_CHAR:\n            printf\("\\n\\n"\);\n            switch \(gs->personaje_elegido\) \{\n)(.*?)(            \}\n            break;\n\n        case GAME_COMBAT:)'
code = re.sub(pattern, r'\g<1>' + cases_code.replace('\\', '\\\\') + r'\g<3>', code, flags=re.DOTALL)

with open('source/game.c', 'w') as f:
    f.write(code)

print("Lore successfully restored.")

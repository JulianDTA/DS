characters = [
    {
        "id": "CANTUNA", "name": "Cantuna", "role": "TANQUE",
        "desc": ["Constructor legendario", "Pacto con el diablo", "Escudos fuertes"],
        "cards": [
            ("Ladrillazo", "FX_ATTACK", 3, 0, 0, 0, ["Arroja un ladrillo frio", "de la iglesia matriz.", "[Dano: 3]"], 3),
            ("Golpe de Piedra", "FX_ATTACK", 2, 0, 0, 0, ["Un bloque tallado a mano,", "pesado como sus pecados.", "[Dano: 2]"], 3),
            ("Avalancha", "FX_ATTACK", 5, 0, 0, 0, ["Invoca la ira del Pichincha", "sobre sus enemigos.", "[Dano: 5]"], 2),
            ("Muro de Piedra", "FX_SHIELD", 0, 2, 0, 0, ["Alza una pared divina", "que resiste los golpes.", "[Escudo: 2]"], 3),
            ("Fortaleza", "FX_SHIELD", 0, 3, 0, 0, ["Un pilar indestructible;", "ni el diablo puede pasar.", "[Escudo: 3]"], 3),
            ("Descanso", "FX_HEAL", 0, 0, 2, 0, ["Cierra los ojos un momento", "antes del amanecer.", "[Cura: 2 HP]"], 2),
            ("Pacto Diabolico", "FX_HEAL", 0, 0, 4, 0, ["Firma con sangre para", "recuperar su vitalidad.", "[Cura: 4 HP]"], 2),
            ("Planos Secretos", "FX_DRAW", 0, 0, 0, 2, ["Saca un pergamino antiguo", "con nuevas estrategias.", "[Roba: 2]"], 2),
            ("Inspiracion", "FX_DRAW | FX_PLAY_AGAIN", 0, 0, 0, 1, ["Una chispa de ingenio", "le permite actuar rapido.", "[Roba: 1] [+ Juega otra]"], 2),
            ("Contraataque", "FX_ATTACK | FX_SHIELD", 2, 1, 0, 0, ["Se cubre con su mazo", "y devuelve el golpe.", "[Dano: 2] [Escudo: 1]"], 2),
            ("Furia Constructor", "FX_ATTACK | FX_PLAY_AGAIN", 2, 0, 0, 0, ["Trabaja sin descanso,", "atacando repetidas veces.", "[Dano: 2] [+ Juega otra]"], 2),
            ("Bendicion Oscura", "FX_HEAL | FX_DRAW", 0, 0, 2, 1, ["El trato trae beneficios", "ocultos en la penumbra.", "[Cura: 2] [Roba: 1]"], 2)
        ]
    },
    {
        "id": "TINTIN", "name": "El Tin Tin", "role": "AGRESOR",
        "desc": ["Duende travieso", "Aparece en las sombras", "Cadenas de combos"],
        "cards": [
            ("Travesura", "FX_ATTACK", 2, 0, 0, 0, ["Tira de tu cabello", "cuando no estas viendo.", "[Dano: 2]"], 4),
            ("Sombrerazo", "FX_ATTACK", 3, 0, 0, 0, ["Usa su enorme sombrero", "para golpear con fuerza.", "[Dano: 3]"], 3),
            ("Emboscada", "FX_ATTACK", 4, 0, 0, 0, ["Cae desde las ramas", "directo sobre su presa.", "[Dano: 4]"], 3),
            ("Escondite", "FX_SHIELD", 0, 1, 0, 0, ["Se oculta rapidamente", "en la maleza.", "[Escudo: 1]"], 3),
            ("Siesta Maliciosa", "FX_HEAL", 0, 0, 2, 0, ["Descansa un rato para", "planear otra diablura.", "[Cura: 2 HP]"], 2),
            ("Robo de Bolsillos", "FX_DRAW", 0, 0, 0, 2, ["Manos tan rapidas que", "ni sientes que te roba.", "[Roba: 2]"], 3),
            ("Agilidad", "FX_DRAW | FX_PLAY_AGAIN", 0, 0, 0, 1, ["Salta por los aires", "burlando toda defensa.", "[Roba: 1] [+ Juega otra]"], 4),
            ("Golpe Fugaz", "FX_ATTACK | FX_PLAY_AGAIN", 2, 0, 0, 0, ["Pega y desaparece en", "un parpadeo.", "[Dano: 2] [+ Juega otra]"], 3),
            ("Ataque Sorpresa", "FX_ATTACK | FX_DRAW", 3, 0, 0, 1, ["Un golpe por la espalda", "que te deja aturdido.", "[Dano: 3] [Roba: 1]"], 3)
        ]
    },
    {
        "id": "TUNDA", "name": "La Tunda", "role": "CONTROL",
        "desc": ["Bruja del manglar", "Pierna de molinillo", "Curacion y drenaje"],
        "cards": [
            ("Zarpazo", "FX_ATTACK", 3, 0, 0, 0, ["Su mano retorcida", "desgarra la piel.", "[Dano: 3]"], 3),
            ("Molinillazo", "FX_ATTACK", 4, 0, 0, 0, ["Patea con su pesada", "pierna de madera.", "[Dano: 4]"], 3),
            ("Niebla Espesa", "FX_SHIELD", 0, 2, 0, 0, ["El manglar se cierra,", "ocultandola por completo.", "[Escudo: 2]"], 4),
            ("Camarones Magicos", "FX_HEAL", 0, 0, 2, 0, ["Un bocado embrujado", "que restaura su vigor.", "[Cura: 2 HP]"], 4),
            ("Ritual Sanacion", "FX_HEAL", 0, 0, 4, 0, ["Cantos antiguos curan", "sus viejas heridas.", "[Cura: 4 HP]"], 4),
            ("Susurros", "FX_DRAW", 0, 0, 0, 2, ["Voces en la niebla que", "revelan secretos oscuros.", "[Roba: 2]"], 2),
            ("Encantamiento", "FX_DRAW | FX_PLAY_AGAIN", 0, 0, 0, 1, ["Hipnotiza al rival para", "ganar mas tiempo.", "[Roba: 1] [+ Juega otra]"], 2),
            ("Drenar Vida", "FX_ATTACK | FX_HEAL", 2, 0, 2, 0, ["Absorbe tu esencia", "para fortalecerse ella.", "[Dano: 2] [Cura: 2]"], 3),
            ("Maldicion", "FX_ATTACK | FX_SHIELD", 3, 1, 0, 0, ["Un maleficio que lastima", "y a la vez protege.", "[Dano: 3] [Escudo: 1]"], 3)
        ]
    },
    {
        "id": "ALMEIDA", "name": "Padre Almeida", "role": "COMBO",
        "desc": ["Sacerdote rebelde", "Sale de farra", "Mucho robo de cartas"],
        "cards": [
            ("Guitarrazo", "FX_ATTACK", 3, 0, 0, 0, ["Un golpe sonoro con", "su vieja guitarra.", "[Dano: 3]"], 4),
            ("Botellazo", "FX_ATTACK", 4, 0, 0, 0, ["Vuela una botella vacia", "directo a la cabeza.", "[Dano: 4]"], 3),
            ("Sotana", "FX_SHIELD", 0, 2, 0, 0, ["La tela sagrada lo", "protege de los danos.", "[Escudo: 2]"], 3),
            ("Trago Bendito", "FX_HEAL", 0, 0, 3, 0, ["Un buen sorbo para", "olvidar las penas.", "[Cura: 3 HP]"], 3),
            ("Salida Secreta", "FX_DRAW", 0, 0, 0, 3, ["Conoce todos los atajos", "para escapar del convento.", "[Roba: 3]"], 3),
            ("Escape", "FX_DRAW | FX_PLAY_AGAIN", 0, 0, 0, 1, ["Pisa el Cristo y sale", "corriendo a la calle.", "[Roba: 1] [+ Juega otra]"], 5),
            ("Farra", "FX_ATTACK | FX_PLAY_AGAIN", 2, 0, 0, 0, ["Sigue la fiesta con", "golpes impredecibles.", "[Dano: 2] [+ Juega otra]"], 4),
            ("Resaca", "FX_HEAL | FX_DRAW", 0, 0, 1, 1, ["Bebe agua y planea", "su proxima escapada.", "[Cura: 1] [Roba: 1]"], 3)
        ]
    },
    {
        "id": "DAMATAPADA", "name": "Dama Tapada", "role": "TERROR",
        "desc": ["Mujer misteriosa", "Rostro calaverico", "Debuffs y miedo"],
        "cards": [
            ("Aroma Seductor", "FX_DRAW", 0, 0, 0, 2, ["Un perfume floral que", "atrae a sus victimas.", "[Roba: 2]"], 4),
            ("Mirada Paralizante", "FX_ATTACK | FX_PLAY_AGAIN", 2, 0, 0, 0, ["Los ojos del abismo", "te dejan de piedra.", "[Dano: 2] [+ Juega otra]"], 5),
            ("Rostro Esqueletico", "FX_ATTACK", 5, 0, 0, 0, ["Se quita el velo;", "el horror es total.", "[Dano: 5]"], 4),
            ("Grito Aterrador", "FX_ATTACK", 3, 0, 0, 0, ["Un chillido agudo que", "hiela la sangre.", "[Dano: 3]"], 4),
            ("Paseo Nocturno", "FX_SHIELD", 0, 3, 0, 0, ["Camina flotando;", "es dificil golpearla.", "[Escudo: 3]"], 4),
            ("Bruma Fria", "FX_SHIELD", 0, 2, 0, 0, ["Una niebla oscura", "amortigua los golpes.", "[Escudo: 2]"], 4),
            ("Miedo Profundo", "FX_DRAW | FX_PLAY_AGAIN", 0, 0, 0, 1, ["El panico crece", "mientras se acerca.", "[Roba: 1] [+ Juega otra]"], 3)
        ]
    },
    {
        "id": "MARIANGULA", "name": "Maria Angula", "role": "AGRESOR",
        "desc": ["Nina golosa", "Robo tripas del muerto", "Ataques freneticos"],
        "cards": [
            ("Olla Caliente", "FX_ATTACK", 4, 0, 0, 0, ["Lanza caldo hirviendo", "sin pensarlo dos veces.", "[Dano: 4]"], 4),
            ("Cuchillazo", "FX_ATTACK", 3, 0, 0, 0, ["Un corte rapido y", "desesperado.", "[Dano: 3]"], 5),
            ("Panico", "FX_DRAW | FX_PLAY_AGAIN", 0, 0, 0, 1, ["Corre despavorida", "al escuchar los pasos.", "[Roba: 1] [+ Juega otra]"], 5),
            ("Tijeras", "FX_ATTACK | FX_PLAY_AGAIN", 2, 0, 0, 0, ["Corta todo lo que", "se le cruza en frente.", "[Dano: 2] [+ Juega otra]"], 4),
            ("Sopa de Tripas", "FX_HEAL", 0, 0, 3, 0, ["Un banquete macabro", "que restaura energia.", "[Cura: 3 HP]"], 3),
            ("Grito de Culpa", "FX_ATTACK | FX_DRAW", 3, 0, 0, 1, ["Su llanto aterra y", "le da nuevas ideas.", "[Dano: 3] [Roba: 1]"], 4),
            ("Escondite", "FX_SHIELD", 0, 2, 0, 0, ["Se esconde bajo", "las mantas temblando.", "[Escudo: 2]"], 3)
        ]
    },
    {
        "id": "GALLO", "name": "Gallo Catedral", "role": "EQUILIBRADO",
        "desc": ["Gallo de oro", "Canta en la iglesia", "Dano y velocidad"],
        "cards": [
            ("Picotazo", "FX_ATTACK", 3, 0, 0, 0, ["El pico de bronce", "penetra la armadura.", "[Dano: 3]"], 5),
            ("Espolon", "FX_ATTACK", 4, 0, 0, 0, ["Un corte profundo", "con sus garras afiladas.", "[Dano: 4]"], 3),
            ("Canto Matutino", "FX_HEAL | FX_DRAW", 0, 0, 2, 1, ["Anuncia el amanecer,", "renovando su fuerza.", "[Cura: 2] [Roba: 1]"], 4),
            ("Alas de Bronce", "FX_SHIELD", 0, 3, 0, 0, ["Su cuerpo de metal", "rechaza los impactos.", "[Escudo: 3]"], 4),
            ("Vuelo Corto", "FX_DRAW | FX_PLAY_AGAIN", 0, 0, 0, 1, ["Aletea rapidamente", "para tomar ventaja.", "[Roba: 1] [+ Juega otra]"], 4),
            ("Grito Ensordecedor", "FX_ATTACK | FX_PLAY_AGAIN", 2, 0, 0, 0, ["Su canto te aturde", "y te deja vulnerable.", "[Dano: 2] [+ Juega otra]"], 4),
            ("Estatua Posesa", "FX_ATTACK | FX_SHIELD", 4, 2, 0, 0, ["La figura cobra vida,", "pesada y destructiva.", "[Dano: 4] [Escudo: 2]"], 4)
        ]
    },
    {
        "id": "CURA", "name": "Cura sin Cabeza", "role": "MAGIA",
        "desc": ["Sacerdote maldito", "No tiene cabeza", "Magia oscura pura"],
        "cards": [
            ("Llama Negra", "FX_ATTACK", 6, 0, 0, 0, ["Fuego del purgatorio", "que quema el alma.", "[Dano: 6]"], 3),
            ("Sermon Mudo", "FX_ATTACK | FX_PLAY_AGAIN", 2, 0, 0, 0, ["Palabras sin voz", "que destruyen la mente.", "[Dano: 2] [+ Juega otra]"], 4),
            ("Aparicion", "FX_SHIELD", 0, 4, 0, 0, ["Se vuelve incorporeo,", "imposible de tocar.", "[Escudo: 4]"], 3),
            ("Misa de Medianoche", "FX_HEAL", 0, 0, 5, 0, ["Un ritual profano", "que sana sus heridas.", "[Cura: 5 HP]"], 3),
            ("Busqueda de Cabeza", "FX_DRAW", 0, 0, 0, 3, ["Vaga buscando partes", "de su cuerpo perdido.", "[Roba: 3]"], 3),
            ("Condena", "FX_ATTACK | FX_SHIELD", 4, 2, 0, 0, ["El juicio final", "cae sobre ti.", "[Dano: 4] [Escudo: 2]"], 4),
            ("Aura Espectral", "FX_HEAL | FX_DRAW", 0, 0, 2, 1, ["Un frio de ultratumba", "lo rodea por completo.", "[Cura: 2] [Roba: 1]"], 4),
            ("Levitacion", "FX_DRAW | FX_PLAY_AGAIN", 0, 0, 0, 1, ["Flota amenazante", "sobre el empedrado.", "[Roba: 1] [+ Juega otra]"], 4)
        ]
    },
    {
        "id": "CHUZALONGO", "name": "El Chuzalongo", "role": "SALVAJE",
        "desc": ["Criatura del Paramo", "Agresividad pura", "Nula defensa"],
        "cards": [
            ("Mordida Salvaje", "FX_ATTACK", 5, 0, 0, 0, ["Muerde la yugular", "con furia animal.", "[Dano: 5]"], 6),
            ("Garras Paramo", "FX_ATTACK", 4, 0, 0, 0, ["Zarpazos sangrientos", "tejidos de rencor.", "[Dano: 4]"], 5),
            ("Piel Gruesa", "FX_SHIELD", 0, 1, 0, 0, ["El lodo y musgo", "amortiguan un poco.", "[Escudo: 1]"], 3),
            ("Instinto Animal", "FX_DRAW | FX_PLAY_AGAIN", 0, 0, 0, 1, ["Olfatea la sangre", "y actua sin dudar.", "[Roba: 1] [+ Juega otra]"], 4),
            ("Furia Ciega", "FX_ATTACK | FX_PLAY_AGAIN", 3, 0, 0, 0, ["Ataca a todos lados", "sin mirar a quien.", "[Dano: 3] [+ Juega otra]"], 4),
            ("Carne Cruda", "FX_HEAL", 0, 0, 2, 0, ["Se alimenta de lo que", "encuentra en la montana.", "[Cura: 2 HP]"], 3),
            ("Aullido", "FX_ATTACK | FX_DRAW", 4, 0, 0, 1, ["Un grito desgarrador", "que paraliza al enemigo.", "[Dano: 4] [Roba: 1]"], 3)
        ]
    },
    {
        "id": "LLORONA", "name": "La Llorona", "role": "TRISTEZA",
        "desc": ["Madre en pena", "Busca a sus hijos", "Mucha curacion"],
        "cards": [
            ("Mis Hijos!", "FX_ATTACK", 3, 0, 0, 0, ["Un grito de lamento", "que te rompe los timpanos.", "[Dano: 3]"], 4),
            ("Llanto Incesante", "FX_HEAL", 0, 0, 4, 0, ["Sus lagrimas forman", "lagos de desesperacion.", "[Cura: 4 HP]"], 5),
            ("Rio Desbordado", "FX_ATTACK | FX_SHIELD", 3, 2, 0, 0, ["Aguas violentas te", "arrastran lejos de ella.", "[Dano: 3] [Escudo: 2]"], 4),
            ("Manto Blanco", "FX_SHIELD", 0, 3, 0, 0, ["Su tunica espectral", "rechaza los ataques.", "[Escudo: 3]"], 4),
            ("Desesperacion", "FX_DRAW | FX_PLAY_AGAIN", 0, 0, 0, 1, ["Busca frenetica", "por las orillas.", "[Roba: 1] [+ Juega otra]"], 4),
            ("Ahogo", "FX_ATTACK | FX_HEAL", 4, 0, 2, 0, ["Te ahoga en el rio", "para recuperar su fuerza.", "[Dano: 4] [Cura: 2]"], 4),
            ("Lagrimas", "FX_DRAW", 0, 0, 0, 2, ["El dolor le ensena", "nuevas formas de sufrir.", "[Roba: 2]"], 3)
        ]
    },
    {
        "id": "GUAGUAAUCA", "name": "Guagua Auca", "role": "SORPRESA",
        "desc": ["Bebe fantasma", "Demonio enganoso", "Robo y dano"],
        "cards": [
            ("Lloriqueo", "FX_ATTACK", 2, 0, 0, 0, ["Finge estar indefenso", "para atacarte de pronto.", "[Dano: 2]"], 5),
            ("Dientes de Diablo", "FX_ATTACK", 5, 0, 0, 0, ["Muerde el cuello de", "quien lo carga en brazos.", "[Dano: 5]"], 4),
            ("Panales", "FX_SHIELD", 0, 2, 0, 0, ["Usa su apariencia", "inocente como defensa.", "[Escudo: 2]"], 4),
            ("Sorpresa Maligna", "FX_ATTACK | FX_PLAY_AGAIN", 3, 0, 0, 0, ["Revela su verdadera", "forma aterradora.", "[Dano: 3] [+ Juega otra]"], 5),
            ("Risa Macabra", "FX_DRAW", 0, 0, 0, 2, ["Se burla de ti", "mientras toma ventaja.", "[Roba: 2]"], 4),
            ("Inocencia Fingida", "FX_HEAL | FX_DRAW", 0, 0, 3, 1, ["Te da compasion y", "el aprovecha el momento.", "[Cura: 3] [Roba: 1]"], 4),
            ("Mordisco", "FX_ATTACK | FX_SHIELD", 2, 2, 0, 0, ["Muerde y se aleja", "rapidamente.", "[Dano: 2] [Escudo: 2]"], 2)
        ]
    },
    {
        "id": "VIUDA", "name": "Viuda Tamarindo", "role": "TRAMPA",
        "desc": ["Aparece en Guayaquil", "Debajo del tamarindo", "Control total"],
        "cards": [
            ("Seduccion Oscura", "FX_ATTACK | FX_HEAL", 4, 0, 3, 0, ["Te atrae y luego te", "arranca la vitalidad.", "[Dano: 4] [Cura: 3]"], 4),
            ("Abrazo de Muerte", "FX_ATTACK", 5, 0, 0, 0, ["Te abraza fuerte", "hasta asfixiarte.", "[Dano: 5]"], 4),
            ("Sombra del Arbol", "FX_SHIELD", 0, 4, 0, 0, ["Las ramas del viejo", "tamarindo la protegen.", "[Escudo: 4]"], 4),
            ("Velo Negro", "FX_DRAW | FX_PLAY_AGAIN", 0, 0, 0, 1, ["El misterio de su", "rostro oculto.", "[Roba: 1] [+ Juega otra]"], 4),
            ("Ilusion", "FX_ATTACK | FX_PLAY_AGAIN", 2, 0, 0, 0, ["Crees ver a alguien mas", "y bajas la guardia.", "[Dano: 2] [+ Juega otra]"], 4),
            ("Pasion Falsa", "FX_HEAL", 0, 0, 5, 0, ["Un beso embrujado", "que sana a la viuda.", "[Cura: 5 HP]"], 4),
            ("Aroma Dulce", "FX_DRAW", 0, 0, 0, 2, ["Atrae a incautos", "hacia su trampa mortal.", "[Roba: 2]"], 4)
        ]
    }
]

#include "card.h"

const CardData CARTAS_CANTUNA[] = {
    { 4, "Ladrillo Rapido", FX_ATTACK | FX_PLAY_AGAIN, 1, 0, 0, 0, "Arroja un", "ladrillo con", "gran", "velocidad.", NULL, NULL, NULL },
    { 4, "Golpe de Mazo", FX_ATTACK, 3, 0, 0, 0, "Un bloque", "tallado a", "mano, pesado", "como sus", "pecados.", NULL, NULL },
    { 5, "Muro Base", FX_SHIELD | FX_DRAW, 0, 1, 0, 1, "Alza una", "pared", "mientras", "planea.", NULL, NULL, NULL },
    { 4, "Fortaleza", FX_SHIELD, 0, 3, 0, 0, "Un pilar inde", "structible;", "ni el diablo", "puede pasar.", NULL, NULL, NULL },
    { 4, "Descanso", FX_HEAL, 0, 0, 2, 0, "Cierra los", "ojos un", "momento antes", "del amanecer.", NULL, NULL, NULL },
    { 4, "Inspiracion", FX_DRAW | FX_PLAY_AGAIN, 0, 0, 0, 1, "Una chispa de", "ingenio le", "permite", "actuar", "rapido.", NULL, NULL },
    { 1, "Iglesia Terminada", FX_SHIELD | FX_HEAL | FX_ATTACK, 2, 4, 2, 0, "Construye", "todo de", "golpe. Su", "obra maestra.", NULL, NULL, NULL },
    { 1, "Pacto Enganoso", FX_STEAL_HAND | FX_HEAL, 0, 0, 3, 0, "El diablo", "cobra su", "deuda en el", "rival.", NULL, NULL, NULL },
    { 1, "Cimiento Solido", FX_STEAL_DISCARD | FX_SHIELD, 0, 4, 0, 0, "Usa los", "restos para", "blindarse por", "completo.", NULL, NULL, NULL },
    { 1, "Maldicion Paramo", FX_AURA, 1, 0, 0, 0, "Aura", "venenosa.", "Dano 1 al", "rival cada", "turno.", NULL, NULL },
    { 1, "Robo de Cueva", FX_AURA, 0, 0, 0, 1, "Aura ladrona.", "Roba 1 carta", "extra al", "inicio de tu", "turno.", NULL, NULL },
    { 1, "Bendicion Sol", FX_AURA, 0, 0, 1, 0, "Aura", "curativa.", "Cura 1 HP", "pasivamente", "cada turno.", NULL, NULL },
    { 1, "Santuario Oscuro", FX_AURA, 0, 0, 2, 0, "Aura divina.", "Cura 2 HP", "cada turno", "pasivamente.", NULL, NULL, NULL },
};
const int CANTUNA_DECK_SIZE = 13;

const CardData CARTAS_TINTIN[] = {
    { 4, "Travesura", FX_ATTACK | FX_PLAY_AGAIN, 1, 0, 0, 0, "Tira de tu", "cabello y", "sigue", "molestando.", NULL, NULL, NULL },
    { 4, "Emboscada", FX_ATTACK, 3, 0, 0, 0, "Cae desde las", "ramas directo", "sobre su", "presa.", NULL, NULL, NULL },
    { 5, "Escondite", FX_SHIELD | FX_PLAY_AGAIN, 0, 1, 0, 0, "Se oculta", "rapidamente", "en la maleza.", NULL, NULL, NULL, NULL },
    { 4, "Agilidad", FX_DRAW | FX_PLAY_AGAIN, 0, 0, 0, 1, "Salta por los", "aires", "burlando toda", "defensa.", NULL, NULL, NULL },
    { 4, "Siesta Maliciosa", FX_HEAL, 0, 0, 2, 0, "Descansa un", "rato para", "planear otra", "diablura.", NULL, NULL, NULL },
    { 4, "Robo de Bolsillos", FX_STEAL_DECK | FX_ATTACK, 1, 0, 0, 2, "Manos tan", "rapidas que", "ni sientes", "que te roba.", NULL, NULL, NULL },
    { 1, "Seductor Mitico", FX_ATTACK | FX_DRAW | FX_PLAY_AGAIN, 4, 0, 0, 1, "Te engana y", "te roba el", "alma.", NULL, NULL, NULL, NULL },
    { 1, "Sombrero Magico", FX_STEAL_DECK | FX_DRAW | FX_PLAY_AGAIN, 0, 0, 0, 2, "Saca", "sorpresas int", "erminables.", NULL, NULL, NULL, NULL },
    { 1, "Asalto Fugaz", FX_STEAL_HAND | FX_ATTACK, 3, 0, 0, 0, "Te golpea y", "te deja sin", "opciones.", NULL, NULL, NULL, NULL },
    { 1, "Maldicion Paramo", FX_AURA, 1, 0, 0, 0, "Aura", "venenosa.", "Dano 1 al", "rival cada", "turno.", NULL, NULL },
    { 1, "Robo de Cueva", FX_AURA, 0, 0, 0, 1, "Aura ladrona.", "Roba 1 carta", "extra al", "inicio de tu", "turno.", NULL, NULL },
    { 1, "Bendicion Sol", FX_AURA, 0, 0, 1, 0, "Aura", "curativa.", "Cura 1 HP", "pasivamente", "cada turno.", NULL, NULL },
    { 1, "Santuario Oscuro", FX_AURA, 0, 0, 2, 0, "Aura divina.", "Cura 2 HP", "cada turno", "pasivamente.", NULL, NULL, NULL },
};
const int TINTIN_DECK_SIZE = 13;

const CardData CARTAS_TUNDA[] = {
    { 4, "Zarpazo", FX_ATTACK | FX_HEAL, 1, 0, 1, 0, "Su mano", "retorcida", "desgarra y", "absorbe.", NULL, NULL, NULL },
    { 4, "Molinillazo", FX_ATTACK, 3, 0, 0, 0, "Patea con su", "pesada pierna", "de madera.", NULL, NULL, NULL, NULL },
    { 5, "Niebla Espesa", FX_SHIELD | FX_PLAY_AGAIN, 0, 1, 0, 0, "El manglar se", "cierra,", "ocultandola", "por completo.", NULL, NULL, NULL },
    { 4, "Proteccion Lodo", FX_SHIELD, 0, 3, 0, 0, "Barro del", "pantano", "amortigua los", "golpes.", NULL, NULL, NULL },
    { 4, "Camarones Magicos", FX_HEAL, 0, 0, 2, 0, "Un bocado", "embrujado que", "restaura su", "vigor.", NULL, NULL, NULL },
    { 4, "Susurros", FX_DRAW | FX_PLAY_AGAIN, 0, 0, 0, 1, "Voces en la", "niebla que", "revelan", "secretos", "oscuros.", NULL, NULL },
    { 1, "Entundamiento", FX_HEAL | FX_ATTACK | FX_DRAW, 2, 0, 4, 1, "Hipnotiza a", "su presa en", "el fondo del", "bosque.", NULL, NULL, NULL },
    { 1, "Maldicion del Manglar", FX_STEAL_HAND | FX_STEAL_DISCARD, 0, 0, 0, 0, "Pierdes todo", "lo que", "tenias.", NULL, NULL, NULL, NULL },
    { 1, "Ilusion Maternal", FX_STEAL_DECK | FX_HEAL, 0, 0, 3, 0, "Finge ser tu", "madre para", "robar tu", "futuro.", NULL, NULL, NULL },
    { 1, "Maldicion Paramo", FX_AURA, 1, 0, 0, 0, "Aura", "venenosa.", "Dano 1 al", "rival cada", "turno.", NULL, NULL },
    { 1, "Robo de Cueva", FX_AURA, 0, 0, 0, 1, "Aura ladrona.", "Roba 1 carta", "extra al", "inicio de tu", "turno.", NULL, NULL },
    { 1, "Bendicion Sol", FX_AURA, 0, 0, 1, 0, "Aura", "curativa.", "Cura 1 HP", "pasivamente", "cada turno.", NULL, NULL },
    { 1, "Santuario Oscuro", FX_AURA, 0, 0, 2, 0, "Aura divina.", "Cura 2 HP", "cada turno", "pasivamente.", NULL, NULL, NULL },
};
const int TUNDA_DECK_SIZE = 13;

const CardData CARTAS_ALMEIDA[] = {
    { 4, "Guitarrazo", FX_ATTACK | FX_PLAY_AGAIN, 1, 0, 0, 0, "Un golpe", "rapido con su", "vieja", "guitarra.", NULL, NULL, NULL },
    { 4, "Botellazo", FX_ATTACK, 3, 0, 0, 0, "Vuela una", "botella vacia", "directo a la", "cabeza.", NULL, NULL, NULL },
    { 5, "Sotana", FX_SHIELD | FX_DRAW, 0, 1, 0, 1, "La tela", "sagrada lo", "cubre", "mientras", "huye.", NULL, NULL },
    { 4, "Trago Bendito", FX_HEAL | FX_PLAY_AGAIN, 0, 0, 1, 0, "Un pequeno", "sorbo para", "seguir la", "fiesta.", NULL, NULL, NULL },
    { 4, "Salida Secreta", FX_STEAL_DECK | FX_DRAW, 0, 0, 0, 2, "Conoce todos", "los atajos y", "descubre sus", "planes.", NULL, NULL, NULL },
    { 4, "Farra", FX_ATTACK | FX_DRAW, 2, 0, 0, 1, "Sigue la", "fiesta con", "golpes impred", "ecibles.", NULL, NULL, NULL },
    { 1, "Hasta la Vuelta!", FX_DRAW | FX_PLAY_AGAIN | FX_HEAL, 0, 0, 2, 2, "Pisa al", "Cristo y sale", "corriendo", "invencible.", NULL, NULL, NULL },
    { 1, "Escape Milagroso", FX_STEAL_HAND | FX_DRAW, 0, 0, 0, 2, "Esquiva tu", "ataque y huye", "con ventaja.", NULL, NULL, NULL, NULL },
    { 1, "Trago Robado", FX_STEAL_DISCARD | FX_HEAL | FX_PLAY_AGAIN, 0, 0, 2, 0, "Bebe de la", "botella que", "creias vacia.", NULL, NULL, NULL, NULL },
    { 1, "Maldicion Paramo", FX_AURA, 1, 0, 0, 0, "Aura", "venenosa.", "Dano 1 al", "rival cada", "turno.", NULL, NULL },
    { 1, "Robo de Cueva", FX_AURA, 0, 0, 0, 1, "Aura ladrona.", "Roba 1 carta", "extra al", "inicio de tu", "turno.", NULL, NULL },
    { 1, "Bendicion Sol", FX_AURA, 0, 0, 1, 0, "Aura", "curativa.", "Cura 1 HP", "pasivamente", "cada turno.", NULL, NULL },
    { 1, "Santuario Oscuro", FX_AURA, 0, 0, 2, 0, "Aura divina.", "Cura 2 HP", "cada turno", "pasivamente.", NULL, NULL, NULL },
};
const int ALMEIDA_DECK_SIZE = 13;

const CardData CARTAS_DAMATAPADA[] = {
    { 4, "Perfume Barato", FX_ATTACK | FX_PLAY_AGAIN, 1, 0, 0, 0, "Aroma", "embriagador", "que", "desorienta al", "instante.", NULL, NULL },
    { 4, "Grito Aterrador", FX_ATTACK, 3, 0, 0, 0, "Un chillido", "agudo que", "hiela la", "sangre.", NULL, NULL, NULL },
    { 5, "Bruma Fria", FX_SHIELD | FX_DRAW, 0, 1, 0, 1, "Una niebla", "oscura", "amortigua los", "golpes.", NULL, NULL, NULL },
    { 4, "Paseo Nocturno", FX_SHIELD, 0, 3, 0, 0, "Camina", "flotando; es", "dificil", "golpearla.", NULL, NULL, NULL },
    { 4, "Beso Frio", FX_HEAL, 0, 0, 2, 0, "Restaura su", "energia con", "magia negra.", NULL, NULL, NULL, NULL },
    { 4, "Seduccion", FX_DRAW | FX_PLAY_AGAIN, 0, 0, 0, 1, "Atrae a", "incautos", "hacia su", "perdicion.", NULL, NULL, NULL },
    { 1, "Rostro Esqueletico", FX_ATTACK | FX_SHIELD, 4, 3, 0, 0, "Se quita el", "velo; el", "horror", "absoluto.", NULL, NULL, NULL },
    { 1, "Perfume Letal", FX_STEAL_DECK | FX_ATTACK, 4, 0, 0, 0, "El olor a", "muerte", "arruina tu", "destino.", NULL, NULL, NULL },
    { 1, "Mirada al Abismo", FX_STEAL_HAND | FX_STEAL_DECK, 0, 0, 0, 0, "El panico te", "hace perder", "la cabeza.", NULL, NULL, NULL, NULL },
    { 1, "Maldicion Paramo", FX_AURA, 1, 0, 0, 0, "Aura", "venenosa.", "Dano 1 al", "rival cada", "turno.", NULL, NULL },
    { 1, "Robo de Cueva", FX_AURA, 0, 0, 0, 1, "Aura ladrona.", "Roba 1 carta", "extra al", "inicio de tu", "turno.", NULL, NULL },
    { 1, "Bendicion Sol", FX_AURA, 0, 0, 1, 0, "Aura", "curativa.", "Cura 1 HP", "pasivamente", "cada turno.", NULL, NULL },
    { 1, "Santuario Oscuro", FX_AURA, 0, 0, 2, 0, "Aura divina.", "Cura 2 HP", "cada turno", "pasivamente.", NULL, NULL, NULL },
};
const int DAMATAPADA_DECK_SIZE = 13;

const CardData CARTAS_MARIANGULA[] = {
    { 4, "Tijeras", FX_ATTACK | FX_PLAY_AGAIN, 1, 0, 0, 0, "Corta sin", "pensar en las", "consecuencias", ".", NULL, NULL, NULL },
    { 4, "Olla Caliente", FX_ATTACK, 3, 0, 0, 0, "Lanza caldo", "hirviendo sin", "pensarlo dos", "veces.", NULL, NULL, NULL },
    { 5, "Escondite", FX_SHIELD | FX_PLAY_AGAIN, 0, 1, 0, 0, "Se esconde", "temblando", "bajo las", "mantas.", NULL, NULL, NULL },
    { 4, "Miedo a la Noche", FX_SHIELD, 0, 2, 0, 1, "El terror la", "obliga a", "protegerse y", "pensar.", NULL, NULL, NULL },
    { 4, "Robo de Tripas", FX_STEAL_DISCARD | FX_HEAL, 0, 0, 2, 0, "Saca algo", "util de la", "tumba del", "oponente.", NULL, NULL, NULL },
    { 4, "Grito de Culpa", FX_DRAW | FX_PLAY_AGAIN, 0, 0, 0, 1, "Su llanto", "aterra y le", "da nuevas", "ideas.", NULL, NULL, NULL },
    { 1, "Sopa Macabra", FX_ATTACK | FX_HEAL | FX_PLAY_AGAIN, 4, 0, 2, 0, "Cocina el mal", "y se", "fortalece.", NULL, NULL, NULL, NULL },
    { 1, "Sopa de Robos", FX_STEAL_DISCARD | FX_STEAL_HAND, 0, 0, 0, 0, "Saca", "ingredientes", "de donde sea.", NULL, NULL, NULL, NULL },
    { 1, "Berrinche Mortal", FX_STEAL_DECK | FX_ATTACK | FX_PLAY_AGAIN, 2, 0, 0, 0, "Destruye todo", "a su paso.", NULL, NULL, NULL, NULL, NULL },
    { 1, "Maldicion Paramo", FX_AURA, 1, 0, 0, 0, "Aura", "venenosa.", "Dano 1 al", "rival cada", "turno.", NULL, NULL },
    { 1, "Robo de Cueva", FX_AURA, 0, 0, 0, 1, "Aura ladrona.", "Roba 1 carta", "extra al", "inicio de tu", "turno.", NULL, NULL },
    { 1, "Bendicion Sol", FX_AURA, 0, 0, 1, 0, "Aura", "curativa.", "Cura 1 HP", "pasivamente", "cada turno.", NULL, NULL },
    { 1, "Santuario Oscuro", FX_AURA, 0, 0, 2, 0, "Aura divina.", "Cura 2 HP", "cada turno", "pasivamente.", NULL, NULL, NULL },
};
const int MARIANGULA_DECK_SIZE = 13;

const CardData CARTAS_GALLO[] = {
    { 4, "Picotazo Rapido", FX_ATTACK | FX_PLAY_AGAIN, 1, 0, 0, 0, "Un golpe", "veloz con su", "pico de oro.", NULL, NULL, NULL, NULL },
    { 4, "Espolon", FX_ATTACK, 3, 0, 0, 0, "Un corte", "profundo con", "sus garras", "afiladas.", NULL, NULL, NULL },
    { 5, "Vuelo Corto", FX_SHIELD | FX_PLAY_AGAIN, 0, 1, 0, 0, "Aletea", "rapidamente", "para tomar", "ventaja.", NULL, NULL, NULL },
    { 4, "Alas de Bronce", FX_SHIELD, 0, 3, 0, 0, "Su cuerpo de", "metal rechaza", "los impactos.", NULL, NULL, NULL, NULL },
    { 4, "Pluma Dorada", FX_HEAL, 0, 0, 2, 0, "Brillo", "sanador que", "restaura su", "bronce.", NULL, NULL, NULL },
    { 4, "Canto Matutino", FX_DRAW | FX_HEAL, 0, 0, 1, 2, "Anuncia el", "amanecer,", "renovando su", "fuerza.", NULL, NULL, NULL },
    { 1, "Ira de la Catedral", FX_ATTACK | FX_SHIELD | FX_HEAL, 3, 3, 3, 0, "El monumento", "despierta", "castigando al", "blasfemo.", NULL, NULL, NULL },
    { 1, "Canto Hipnotico", FX_STEAL_HAND | FX_SHIELD, 0, 3, 0, 0, "Te aturde", "mientras se", "protege.", NULL, NULL, NULL, NULL },
    { 1, "Brillo Cegador", FX_STEAL_DISCARD | FX_DRAW | FX_PLAY_AGAIN, 0, 0, 0, 1, "Resplandece y", "toma la", "iniciativa.", NULL, NULL, NULL, NULL },
    { 1, "Maldicion Paramo", FX_AURA, 1, 0, 0, 0, "Aura", "venenosa.", "Dano 1 al", "rival cada", "turno.", NULL, NULL },
    { 1, "Robo de Cueva", FX_AURA, 0, 0, 0, 1, "Aura ladrona.", "Roba 1 carta", "extra al", "inicio de tu", "turno.", NULL, NULL },
    { 1, "Bendicion Sol", FX_AURA, 0, 0, 1, 0, "Aura", "curativa.", "Cura 1 HP", "pasivamente", "cada turno.", NULL, NULL },
    { 1, "Santuario Oscuro", FX_AURA, 0, 0, 2, 0, "Aura divina.", "Cura 2 HP", "cada turno", "pasivamente.", NULL, NULL, NULL },
};
const int GALLO_DECK_SIZE = 13;

const CardData CARTAS_CURA[] = {
    { 4, "Sermon Mudo", FX_ATTACK | FX_PLAY_AGAIN, 1, 0, 0, 0, "Palabras sin", "voz que", "destruyen la", "mente.", NULL, NULL, NULL },
    { 4, "Llama Negra", FX_ATTACK, 3, 0, 0, 0, "Fuego del", "purgatorio", "que quema el", "alma.", NULL, NULL, NULL },
    { 5, "Levitacion", FX_SHIELD | FX_DRAW, 0, 1, 0, 1, "Flota", "amenazante", "sobre el", "empedrado.", NULL, NULL, NULL },
    { 4, "Aparicion", FX_SHIELD, 0, 3, 0, 0, "Se vuelve", "incorporeo,", "imposible de", "tocar.", NULL, NULL, NULL },
    { 4, "Aura Espectral", FX_HEAL, 0, 0, 2, 0, "Un frio de", "ultratumba lo", "rodea por", "completo.", NULL, NULL, NULL },
    { 4, "Busqueda de Cabeza", FX_DRAW | FX_PLAY_AGAIN, 0, 0, 0, 1, "Vaga buscando", "partes de su", "cuerpo", "perdido.", NULL, NULL, NULL },
    { 1, "Misa de Medianoche", FX_ATTACK | FX_DRAW | FX_PLAY_AGAIN, 4, 0, 0, 2, "Un ritual", "profano que", "condena al", "enemigo.", NULL, NULL, NULL },
    { 1, "Fuego del Purgatorio", FX_STEAL_DECK | FX_ATTACK, 5, 0, 0, 0, "Quema tu", "esperanza.", NULL, NULL, NULL, NULL, NULL },
    { 1, "Exorcismo Inverso", FX_STEAL_HAND | FX_HEAL, 0, 0, 4, 0, "Te drena el", "alma.", NULL, NULL, NULL, NULL, NULL },
    { 1, "Maldicion Paramo", FX_AURA, 1, 0, 0, 0, "Aura", "venenosa.", "Dano 1 al", "rival cada", "turno.", NULL, NULL },
    { 1, "Robo de Cueva", FX_AURA, 0, 0, 0, 1, "Aura ladrona.", "Roba 1 carta", "extra al", "inicio de tu", "turno.", NULL, NULL },
    { 1, "Bendicion Sol", FX_AURA, 0, 0, 1, 0, "Aura", "curativa.", "Cura 1 HP", "pasivamente", "cada turno.", NULL, NULL },
    { 1, "Santuario Oscuro", FX_AURA, 0, 0, 2, 0, "Aura divina.", "Cura 2 HP", "cada turno", "pasivamente.", NULL, NULL, NULL },
};
const int CURA_DECK_SIZE = 13;

const CardData CARTAS_CHUZALONGO[] = {
    { 4, "Furia Ciega", FX_ATTACK | FX_PLAY_AGAIN, 1, 0, 0, 0, "Ataca a todos", "lados sin", "mirar a", "quien.", NULL, NULL, NULL },
    { 4, "Garras Paramo", FX_ATTACK, 3, 0, 0, 0, "Zarpazos", "sangrientos", "tejidos de", "rencor.", NULL, NULL, NULL },
    { 5, "Instinto Animal", FX_SHIELD | FX_PLAY_AGAIN, 0, 1, 0, 0, "Olfatea la", "sangre y", "actua sin", "dudar.", NULL, NULL, NULL },
    { 4, "Piel Gruesa", FX_SHIELD, 0, 2, 0, 1, "El lodo y", "musgo", "amortiguan un", "poco.", NULL, NULL, NULL },
    { 4, "Carne Cruda", FX_HEAL, 0, 0, 2, 0, "Se alimenta", "de lo que", "encuentra en", "la montana.", NULL, NULL, NULL },
    { 4, "Aullido", FX_DRAW | FX_ATTACK, 2, 0, 0, 1, "Un grito", "desgarrador", "que paraliza", "al enemigo.", NULL, NULL, NULL },
    { 1, "Mordida Salvaje", FX_ATTACK | FX_HEAL | FX_PLAY_AGAIN, 4, 0, 2, 0, "Muerde la", "yugular con", "furia animal.", NULL, NULL, NULL, NULL },
    { 1, "Ataque Furtivo", FX_STEAL_HAND | FX_ATTACK, 4, 0, 0, 0, "Muerde y se", "roba lo que", "caiga.", NULL, NULL, NULL, NULL },
    { 1, "Carrona", FX_STEAL_DISCARD | FX_HEAL | FX_DRAW, 0, 0, 2, 1, "Se alimenta", "de tus", "restos.", NULL, NULL, NULL, NULL },
    { 1, "Maldicion Paramo", FX_AURA, 1, 0, 0, 0, "Aura", "venenosa.", "Dano 1 al", "rival cada", "turno.", NULL, NULL },
    { 1, "Robo de Cueva", FX_AURA, 0, 0, 0, 1, "Aura ladrona.", "Roba 1 carta", "extra al", "inicio de tu", "turno.", NULL, NULL },
    { 1, "Bendicion Sol", FX_AURA, 0, 0, 1, 0, "Aura", "curativa.", "Cura 1 HP", "pasivamente", "cada turno.", NULL, NULL },
    { 1, "Santuario Oscuro", FX_AURA, 0, 0, 2, 0, "Aura divina.", "Cura 2 HP", "cada turno", "pasivamente.", NULL, NULL, NULL },
};
const int CHUZALONGO_DECK_SIZE = 13;

const CardData CARTAS_LLORONA[] = {
    { 4, "Lagrimas", FX_ATTACK | FX_PLAY_AGAIN, 1, 0, 0, 0, "El dolor le", "ensena nuevas", "formas de", "sufrir.", NULL, NULL, NULL },
    { 4, "Mis Hijos!", FX_ATTACK, 3, 0, 0, 0, "Un grito de", "lamento que", "te rompe los", "timpanos.", NULL, NULL, NULL },
    { 5, "Manto Blanco", FX_SHIELD | FX_HEAL, 0, 1, 1, 0, "Su tunica", "espectral", "rechaza los", "ataques.", NULL, NULL, NULL },
    { 4, "Rio Desbordado", FX_SHIELD, 0, 3, 0, 0, "Aguas", "violentas te", "arrastran", "lejos de", "ella.", NULL, NULL },
    { 4, "Consuelo Vano", FX_HEAL, 0, 0, 2, 0, "Se engana", "pensando que", "aun estan", "vivos.", NULL, NULL, NULL },
    { 4, "Desesperacion", FX_DRAW | FX_PLAY_AGAIN, 0, 0, 0, 1, "Busca", "frenetica por", "las orillas.", NULL, NULL, NULL, NULL },
    { 1, "Ahogo Profundo", FX_HEAL | FX_SHIELD | FX_ATTACK, 2, 4, 4, 0, "Te sumerge en", "su eterno", "sufrimiento.", NULL, NULL, NULL, NULL },
    { 1, "Llanto Ahogado", FX_STEAL_DECK | FX_SHIELD, 0, 4, 0, 0, "Sus lagrimas", "forman una", "barrera.", NULL, NULL, NULL, NULL },
    { 1, "Arrastrar al Fondo", FX_STEAL_DISCARD | FX_ATTACK | FX_HEAL, 2, 0, 2, 0, "Te hunde con", "ella.", NULL, NULL, NULL, NULL, NULL },
    { 1, "Maldicion Paramo", FX_AURA, 1, 0, 0, 0, "Aura", "venenosa.", "Dano 1 al", "rival cada", "turno.", NULL, NULL },
    { 1, "Robo de Cueva", FX_AURA, 0, 0, 0, 1, "Aura ladrona.", "Roba 1 carta", "extra al", "inicio de tu", "turno.", NULL, NULL },
    { 1, "Bendicion Sol", FX_AURA, 0, 0, 1, 0, "Aura", "curativa.", "Cura 1 HP", "pasivamente", "cada turno.", NULL, NULL },
    { 1, "Santuario Oscuro", FX_AURA, 0, 0, 2, 0, "Aura divina.", "Cura 2 HP", "cada turno", "pasivamente.", NULL, NULL, NULL },
};
const int LLORONA_DECK_SIZE = 13;

const CardData CARTAS_GUAGUAAUCA[] = {
    { 4, "Lloriqueo", FX_ATTACK | FX_PLAY_AGAIN, 1, 0, 0, 0, "Finge estar", "indefenso", "para atacarte", "de pronto.", NULL, NULL, NULL },
    { 4, "Sorpresa Maligna", FX_ATTACK, 3, 0, 0, 0, "Revela su", "verdadera", "forma", "aterradora.", NULL, NULL, NULL },
    { 5, "Panales", FX_SHIELD | FX_PLAY_AGAIN, 0, 1, 0, 0, "Usa su", "apariencia", "inocente como", "defensa.", NULL, NULL, NULL },
    { 4, "Inocencia Fingida", FX_STEAL_HAND | FX_SHIELD, 0, 2, 0, 1, "Te da", "compasion y", "te roba lo", "que tienes.", NULL, NULL, NULL },
    { 4, "Biberon de Sangre", FX_HEAL, 0, 0, 2, 0, "Se alimenta", "de tu piedad.", NULL, NULL, NULL, NULL, NULL },
    { 4, "Risa Macabra", FX_DRAW | FX_PLAY_AGAIN, 0, 0, 0, 1, "Se burla de", "ti mientras", "toma ventaja.", NULL, NULL, NULL, NULL },
    { 1, "Dientes de Diablo", FX_ATTACK | FX_DRAW | FX_PLAY_AGAIN, 4, 0, 0, 2, "Muerde el", "cuello de", "quien lo", "carga.", NULL, NULL, NULL },
    { 1, "Berrinche Infernal", FX_STEAL_DECK | FX_STEAL_DISCARD, 0, 0, 0, 0, "Un demonio", "desatado", "robando por", "doquier.", NULL, NULL, NULL },
    { 1, "Muerde Dedos", FX_STEAL_HAND | FX_ATTACK | FX_PLAY_AGAIN, 2, 0, 0, 0, "Engana y", "ataca muy", "rapido.", NULL, NULL, NULL, NULL },
    { 1, "Maldicion Paramo", FX_AURA, 1, 0, 0, 0, "Aura", "venenosa.", "Dano 1 al", "rival cada", "turno.", NULL, NULL },
    { 1, "Robo de Cueva", FX_AURA, 0, 0, 0, 1, "Aura ladrona.", "Roba 1 carta", "extra al", "inicio de tu", "turno.", NULL, NULL },
    { 1, "Bendicion Sol", FX_AURA, 0, 0, 1, 0, "Aura", "curativa.", "Cura 1 HP", "pasivamente", "cada turno.", NULL, NULL },
    { 1, "Santuario Oscuro", FX_AURA, 0, 0, 2, 0, "Aura divina.", "Cura 2 HP", "cada turno", "pasivamente.", NULL, NULL, NULL },
};
const int GUAGUAAUCA_DECK_SIZE = 13;

const CardData CARTAS_VIUDA[] = {
    { 4, "Ilusion", FX_ATTACK | FX_PLAY_AGAIN, 1, 0, 0, 0, "Crees ver a", "alguien mas y", "bajas la", "guardia.", NULL, NULL, NULL },
    { 4, "Borracho Perdido", FX_ATTACK, 3, 0, 0, 0, "Engana a sus", "victimas", "hasta", "dejarlas", "vacias.", NULL, NULL },
    { 5, "Aroma Dulce", FX_SHIELD | FX_PLAY_AGAIN, 0, 1, 0, 0, "Atrae a", "incautos", "hacia su", "trampa", "mortal.", NULL, NULL },
    { 4, "Sombra del Arbol", FX_SHIELD, 0, 3, 0, 0, "Las ramas del", "viejo", "tamarindo la", "protegen.", NULL, NULL, NULL },
    { 4, "Pasion Falsa", FX_HEAL, 0, 0, 2, 0, "Un beso", "embrujado que", "sana a la", "viuda.", NULL, NULL, NULL },
    { 4, "Velo Negro", FX_STEAL_HAND | FX_PLAY_AGAIN, 0, 0, 0, 1, "Te nubla la", "mente y", "pierdes tu", "mejor carta.", NULL, NULL, NULL },
    { 1, "Abrazo de Muerte", FX_ATTACK | FX_HEAL | FX_SHIELD, 4, 2, 3, 0, "Te abraza", "fuerte hasta", "asfixiarte.", NULL, NULL, NULL, NULL },
    { 1, "Seduccion Oscura", FX_STEAL_DECK | FX_STEAL_HAND, 0, 0, 0, 0, "El engano", "perfecto.", NULL, NULL, NULL, NULL, NULL },
    { 1, "Asfixia", FX_STEAL_DISCARD | FX_ATTACK | FX_PLAY_AGAIN, 3, 0, 0, 0, "Te roba el", "aire y tus", "recuerdos.", NULL, NULL, NULL, NULL },
    { 1, "Maldicion Paramo", FX_AURA, 1, 0, 0, 0, "Aura", "venenosa.", "Dano 1 al", "rival cada", "turno.", NULL, NULL },
    { 1, "Robo de Cueva", FX_AURA, 0, 0, 0, 1, "Aura ladrona.", "Roba 1 carta", "extra al", "inicio de tu", "turno.", NULL, NULL },
    { 1, "Bendicion Sol", FX_AURA, 0, 0, 1, 0, "Aura", "curativa.", "Cura 1 HP", "pasivamente", "cada turno.", NULL, NULL },
    { 1, "Santuario Oscuro", FX_AURA, 0, 0, 2, 0, "Aura divina.", "Cura 2 HP", "cada turno", "pasivamente.", NULL, NULL, NULL },
};
const int VIUDA_DECK_SIZE = 13;


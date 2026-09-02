import re

with open('include/deck.h', 'r') as f:
    content = f.read()

content = content.replace('void deck_init(', 'int deck_rng_next();\nvoid deck_init(')

with open('include/deck.h', 'w') as f:
    f.write(content)

with open('source/deck.c', 'r') as f:
    content = f.read()

content = content.replace('static int rng_next() {', 'int deck_rng_next() {')
content = content.replace('rng_next()', 'deck_rng_next()')

with open('source/deck.c', 'w') as f:
    f.write(content)

with open('source/combat.c', 'r') as f:
    content = f.read()

content = content.replace('int r = rand() % defensor->deck.mano_size;', 'int r = deck_rng_next() % defensor->deck.mano_size;')

with open('source/combat.c', 'w') as f:
    f.write(content)

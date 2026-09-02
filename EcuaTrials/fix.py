with open('source/deck.c', 'r') as f:
    code = f.read()

code = code.replace("int deck_deck_rng_next() {", "int deck_rng_next() {")

with open('source/deck.c', 'w') as f:
    f.write(code)

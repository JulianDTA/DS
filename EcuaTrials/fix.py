import re

with open('source/game.c', 'r') as f:
    code = f.read()

# Replace all literal \\n with \n
code = code.replace('\\\\n', '\\n')

with open('source/game.c', 'w') as f:
    f.write(code)

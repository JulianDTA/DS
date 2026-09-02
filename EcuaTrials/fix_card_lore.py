import re

with open('source/game.c', 'r') as f:
    code = f.read()

code = code.replace('printf("\\\\x1b[7;6H%s", hover->lore1);', 'printf("\\\\x1b[7;3H%s", hover->lore1);')
code = code.replace('printf("\\\\x1b[8;6H%s", hover->lore2);', 'printf("\\\\x1b[8;3H%s", hover->lore2);')
code = code.replace('printf("\\\\x1b[9;6H%s", hover->lore3);', 'printf("\\\\x1b[9;3H%s", hover->lore3);')
code = code.replace('printf("\\\\x1b[10;6H%s", hover->lore4);', 'printf("\\\\x1b[10;3H%s", hover->lore4);')
code = code.replace('printf("\\\\x1b[11;6H%s", hover->lore5);', 'printf("\\\\x1b[11;3H%s", hover->lore5);')
code = code.replace('printf("\\\\x1b[12;6H%s", hover->lore6);', 'printf("\\\\x1b[12;3H%s", hover->lore6);')
code = code.replace('printf("\\\\x1b[13;6H%s", hover->lore7);', 'printf("\\\\x1b[13;3H%s", hover->lore7);')

code = code.replace('printf("\\\\x1b[7;21HEfecto:");', 'printf("\\\\x1b[7;22HEfecto:");')
code = code.replace('printf("\\\\x1b[8;21HATQ: %d"', 'printf("\\\\x1b[8;22HATQ: %d"')
code = code.replace('printf("\\\\x1b[8;21HDEF: %d"', 'printf("\\\\x1b[8;22HDEF: %d"')
code = code.replace('printf("\\\\x1b[8;21HCUR: %d"', 'printf("\\\\x1b[8;22HCUR: %d"')
code = code.replace('printf("\\\\x1b[8;21HAURA"', 'printf("\\\\x1b[8;22HAURA"')

# And wait, the "[+Juega]" text is printed further down! Where is it? Let's check!

import textwrap
import ast

with open('source/cards_data.py', 'r') as f:
    content = f.read()

start_idx = content.find('[{')
end_idx = content.rfind('}]') + 2
list_str = content[start_idx:end_idx]

env = {}
exec('data = ' + list_str, env)
characters = env['data']

c_code = '#include \"card.h\"\n\n'

for group in characters:
    cid = group['id']
    var_name = f'CARTAS_{cid}'
    c_code += f'const CardData {var_name}[] = {{\n'
    
    for card in group['cards']:
        c_id = card[0]
        c_eff = card[1]
        if not c_eff: c_eff = '0'
        c_atk = card[2]
        c_sh = card[3]
        c_hl = card[4]
        c_dr = card[5]
        
        full_lore = ' '.join([line for line in card[6] if not line.startswith('[') and line.strip()])
        wrapped_lore = textwrap.wrap(full_lore, width=13)
        if len(wrapped_lore) > 7:
            wrapped_lore = wrapped_lore[:7]
            
        lore_lines = ['NULL'] * 7
        for i, line in enumerate(wrapped_lore):
            lore_lines[i] = f'\"{line}\"'
            
        c_code += f'    {{ {card[7]}, \"{c_id}\", {c_eff}, {c_atk}, {c_sh}, {c_hl}, {c_dr}, {lore_lines[0]}, {lore_lines[1]}, {lore_lines[2]}, {lore_lines[3]}, {lore_lines[4]}, {lore_lines[5]}, {lore_lines[6]} }},\n'
        
    c_code += '};\n'
    c_code += f'const int {cid}_DECK_SIZE = {len(group["cards"])};\n\n'

with open('source/card.c', 'w') as f:
    f.write(c_code)

from PIL import Image
img = Image.open('gfx/bg_bottom.png').convert('RGB')
min_y = 192
max_y = 0
for y in range(0, 192):
    p = img.getpixel((128, y))
    if p[0] < 50: # The black outline
        min_y = min(min_y, y)
        max_y = max(max_y, y)
print(f'Slots span vertically from {min_y} to {max_y}')

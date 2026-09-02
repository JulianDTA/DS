from PIL import Image
img = Image.open('gfx/touch_bg.png').convert('RGB')
min_x = 256
max_x = 0
for x in range(0, 256):
    p = img.getpixel((x, 120))
    if p[0] < 50:
        min_x = min(min_x, x)
        max_x = max(max_x, x)
print(f'Slots span from {min_x} to {max_x}')

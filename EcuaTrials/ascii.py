from PIL import Image
img = Image.open('gfx/bg_bottom.png').convert('L')
chars = ' .:-=+*#%@'
for y in range(0, 192, 4):
    line = ''
    for x in range(0, 256, 4):
        p = img.getpixel((x, y))
        line += chars[int(p / 255.0 * 9)]
    print(line)

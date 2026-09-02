from PIL import Image

img = Image.open('gfx/bg_bottom.png').convert('RGB')

# Source block: clean wood from left side (away from compass rose)
strip = img.crop((16, 36, 76, 98)) # 60x62

# Paste it repeatedly across the card slot area
for x in range(14, 242, 60):
    img.paste(strip, (x, 108))

img.save('gfx/bg_bottom.png')

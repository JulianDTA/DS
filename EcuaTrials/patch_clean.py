from PIL import Image

img = Image.open('gfx/bg_bottom.png').convert('RGB')

# The left side of the panel is clean (no compass rose)
# Crop from x=16 to x=86 (width 70), y=40 to y=102 (height 62)
clean_wood = img.crop((16, 40, 86, 102))

# The card slots are roughly between x=16 and x=240, and y=106 and y=168.
# Paste the clean wood across the entire width of the card slots
for x in range(16, 240, 70):
    img.paste(clean_wood, (x, 106))

# Let's also do a little bit of blending if needed, but it should be fine.
img.save('gfx/bg_bottom.png')

from PIL import Image

img = Image.open('gfx/bg_bottom.png').convert('RGB')

# 1. Take a clean horizontal strip of wood from JUST above the slots.
# x=16 to 240 (width 224). y=94 to 106 (height 12).
clean_strip = img.crop((16, 94, 240, 106))

# 2. We need to cover from y=106 to y=168 (height 62).
# Create a patch of 224x62
patch = Image.new('RGB', (224, 62))

# 3. Tile the 12px high strip vertically inside the patch
for y in range(0, 62, 12):
    patch.paste(clean_strip, (0, y))

# 4. Paste the perfectly sized patch back into the image!
img.paste(patch, (16, 106))

img.save('gfx/bg_bottom.png')
